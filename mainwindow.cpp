#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QStandardPaths>
#include "desc_pdialog.h"

MainWindow *MainWindow::instance=nullptr;
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  loadGpoMinerolist();
  loadDataListCliente();
  loadMesesAnios();
  loadDataEstMonitoreo();

  ui->deFecha->setDate(QDate::currentDate());
  ui->teHora->setTime(QTime::currentTime());

  loadCboTemas();
  loadSettings();


  saveImageContextMenu();
  defaultImage();
  haveData();

  QObject::connect(ui->txtDesc_punto,&SWCustomTxt::clicked,this,[&](){
    Desc_pDialog *desc_dialog=new Desc_pDialog(1,ui->txtDesc_punto->text(),this);
    desc_dialog->exec();

  });
  //  qDebug()<<"tura relativa: "<<bLayer.relativePath();

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::loadGpoMinerolist()
{
  dataList=bLayer.gpoMineroList(BussinesLayer::GPO_MINERO);
  if(dataList.isEmpty()){
    //    QMessageBox::critical(this,qApp->applicationName(),"Error al cargar los datos\n"+
    //                          bLayer.errorMessage());
    return;
  }

  ui->cboGrupo->addItems(dataList.values());
  //  loadDataListCliente();
  //  loadDataEstMonitoreo();
}

void MainWindow::loadDataListCliente()
{

  dataListCliente=bLayer.gpoMineroList(BussinesLayer::CLIENTE,
                                         dataList.key(ui->cboGrupo->currentText()));
  if(dataListCliente.isEmpty()){
    //    QMessageBox::critical(this,qApp->applicationName(),"Error al cargar los datos\n"+
    //                                                           bLayer.errorMessage());
    return;
  }
  ui->cboUnidad->addItems(dataListCliente.values());

}

void MainWindow::loadDataEstMonitoreo()
{
  //  dataList_2.clear();
  if(ui->lwEstaciones->model()->rowCount()!=0)
    ui->lwEstaciones->clear();
  dataList_2=bLayer.selectCodEstacion(ui->cboAnios->currentData(Qt::DisplayRole).toInt(),
                                        meses.key(ui->cboMeses->currentText()),
                                        dataListCliente.key(ui->cboUnidad->currentText()));

  //  ui->lwEstaciones->addItems(dataList_2.values());
  if(!dataList_2.isEmpty()){
    QStringList l=dataList_2.values();
    for(int i=0;i<dataList_2.count();++i){
      QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/ui-11-128.png"),l.value(i));
      ui->lwEstaciones->addItem(item);
    }

    QListWidgetItem *item=ui->lwEstaciones->item(0);
    ui->lwEstaciones->setCurrentItem(item,QItemSelectionModel::Select);
  }
  if(dataList_2.isEmpty()){
    cleanControls();
    ui->actionGuardar_foto->setDisabled(true);
    ui->actionGuardar_foto_como->setDisabled(true);
    defaultImage();
  }
}

void MainWindow::saveImageContextMenu()
{

  ui->lblfoto->setContextMenuPolicy(Qt::ActionsContextMenu);
  ui->lblfoto->addAction(ui->actionGuardar_foto);
  ui->lblfoto->addAction(ui->actionGuardar_foto_como);

  //  ui->actionGuardar_foto->setEnabled(true);
  //  ui->actionGuardar_foto_como->setEnabled(true);
  QObject::connect(ui->actionGuardar_foto,&QAction::triggered,[this](){
    QStringList paths=QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString pathToSave=paths.first();
    pathToSave.append("/");
    pathToSave.append(ui->cboUnidad->currentText());
    pathToSave.append("_");
    pathToSave.append(ui->txtEstacion->text());
    pathToSave.append("_");
    pathToSave.append(ui->deFecha->date().toString());
    pathToSave.append("_");

    QFile file;
    QFileInfo info;

    QString currentPicture=ui->lwFotos->currentItem()->data(Qt::DisplayRole).toString();
    if(!currentPicture.isEmpty()){
      if(currentPicture.compare("Foto 1")==0){
        file.setFileName(dataList_monitoreo.value(4).toString());
        info.setFile(file);
        //        qDebug()<<currentPicture<<Qt::endl;
        //        qDebug()<<dataList_monitoreo.value(4).toString();
        pathToSave.append(info.fileName());

      }
      else if(currentPicture.compare("Foto 2")==0){
        file.setFileName(dataList_monitoreo.value(5).toString());
        info.setFile(file);
        pathToSave.append(info.fileName());
        //        qDebug()<<currentPicture<<Qt::endl;
        //        qDebug()<<dataList_monitoreo.value(5).toString();
      }else{
        file.setFileName(dataList_monitoreo.value(6).toString());
        info.setFile(file);
        pathToSave.append(info.fileName());
        //        qDebug()<<currentPicture<<Qt::endl;
        //        qDebug()<<dataList_monitoreo.value(6).toString();
      }
    }

    if(!file.copy(pathToSave)){
      QMessageBox::warning(this,qApp->applicationName(),"Error al guardar el archivo\n"
                                                          "No puede guardar el mismo archivo en la misma dirección.");
      return;
    }
    QMessageBox::information(this,qApp->applicationName(),"Archivo guardado en:\n"+pathToSave);
  });


  QObject::connect(ui->actionGuardar_foto_como,&QAction::triggered,[this](){
    QStringList path=QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);

    QString fileName=QFileDialog::getSaveFileName(this,"Guardar foto",QDir::current().path(),
                                                    "Imagenes (*.jpg)");
    if(fileName.isEmpty())
      return;
    QFile file;
    QString currentPicture=ui->lwFotos->currentItem()->data(Qt::DisplayRole).toString();
    if(!currentPicture.isEmpty()){
      if(currentPicture.compare("Foto 1")==0)
        file.setFileName(dataList_monitoreo.value(4).toString());
      else if(currentPicture.compare("Foto 2")==0){
        file.setFileName(dataList_monitoreo.value(5).toString());
      }else{
        file.setFileName(dataList_monitoreo.value(6).toString());
      }
    }
    if(!file.copy(fileName)){
      QMessageBox::critical(this,qApp->applicationName(),"Error al guardar el archivo");
      return;
    }
    QMessageBox::information(this,qApp->applicationName(),"Archivo guardado");
  });

}

void MainWindow::loadCboTemas()
{
  cboTemas=new QComboBox(this);
  cboTemas->addItem("Tema claro");
  cboTemas->addItem("Tema oscuro");
  ui->toolBar->addWidget(cboTemas);
  QObject::connect(cboTemas,QOverload<int>::of(&QComboBox::activated),this,[&](){
    cboTemas->currentIndex()==0 ? QEasySettings::setStyle(QEasySettings::Style::lightFusion) :
                                  QEasySettings::setStyle(QEasySettings::Style::darkFusion);

  });
  ui->lblfoto->setScaledContents(true);
  ui->lblfoto->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

}

void MainWindow::on_toolButton_clicked()
{
  nuevoFrm=new NuevoDialog(NuevoDialog::GRUPO,QVariantList(),this);
  nuevoFrm->setWindowTitle(tr("Nuevo consorcio o grupo minero"));
  if(nuevoFrm->exec()==QDialog::Accepted){
    ui->cboGrupo->clear();
    loadGpoMinerolist();
    haveData();
  }
}

void MainWindow::on_toolButton_2_clicked()
{
  nuevoFrm=new NuevoDialog(NuevoDialog::UNIDAD,QVariantList(), this);
  nuevoFrm->setWindowTitle(tr("Nueva unidad minera"));
  if(nuevoFrm->exec()==QDialog::Accepted){
    ui->cboUnidad->clear();
    loadDataListCliente();
    ui->lwEstaciones->clear();
    loadDataEstMonitoreo();

  }

}

void MainWindow::on_cboGrupo_activated(int index)
{
  Q_UNUSED(index)

  ui->cboUnidad->clear();
  loadDataListCliente();
  //  ui->lwEstaciones->clear();
  loadDataEstMonitoreo();

  if(dataList_2.isEmpty()){
    cleanControls();
    ui->actionGuardar_foto->setDisabled(true);
    ui->actionGuardar_foto_como->setDisabled(true);
    defaultImage();
  }
  haveData();

}
void MainWindow::on_actionNuevo_punto_de_monitoreo_triggered()
{
  nuevaEstFrm=new NuevaEstMonitoreoDialog(this);
  nuevaEstFrm->setWindowTitle(qApp->applicationName().append(" - Nuevo"));
  if(nuevaEstFrm->exec()==QDialog::Accepted){
    ui->lwEstaciones->clear();
    loadDataEstMonitoreo();
    haveData();
  }
}

void MainWindow::on_cboUnidad_activated(int index)
{
  Q_UNUSED(index)

  loadDataEstMonitoreo();

  if(dataList_2.isEmpty()){
    cleanControls();
    ui->actionGuardar_foto->setDisabled(true);
    ui->actionGuardar_foto_como->setDisabled(true);
    defaultImage();
  }
  haveData();
}

void MainWindow::loadMesesAnios()
{

  for(int i=1;i<=ui->deFecha->calendar().monthsInYear(QDate::currentDate().year());i++){
    meses.insert(i,ui->deFecha->calendar().monthName(QLocale::system(),i));
  }
  QList<int> m=meses.keys();
  std::sort(m.begin(),m.end());
  for(int i:m){
    ui->cboMeses->addItem(meses.value(i));
  }
  ui->cboMeses->setCurrentIndex(QDate::currentDate().month()-1);

  //años
  anio=2000;
  for(int i=anio;i<=QDate::currentDate().year();++i){
    ui->cboAnios->addItem(QString::number(i));
  }
  ui->cboAnios->setCurrentIndex(ui->cboAnios->count()-1);
}

void MainWindow::loadSettings()
{
  QEasySettings::init(QEasySettings::Format::regFormat,qApp->organizationName());
  setGeometry(QEasySettings::readSettings("w_setting","w_pos_geometry").toRect());
  QEasySettings::setStyle(QEasySettings::readStyle());
  if(QEasySettings::readStyle()==QEasySettings::Style::lightFusion)
    cboTemas->setCurrentIndex(0);
  else
    cboTemas->setCurrentIndex(1);
}

void MainWindow::datosMonitoreo()
{
  int nro=bLayer.nro(dataList_2.key(ui->lwEstaciones->currentItem()->data(Qt::DisplayRole).toString()));
  dataList_monitoreo=bLayer.dataEstMonitoreo(nro);
  ui->txtEstacion->setText(dataList_monitoreo.value(0).toString());
  ui->deFecha->setDate(dataList_monitoreo.value(1).toDate());
  ui->teHora->setTime(dataList_monitoreo.value(2).toTime());
  ui->txtDescripcion->setPlainText(dataList_monitoreo.value(3).toString());
  ui->lwFotos->clear();

  if(!dataList_monitoreo.value(4).toString().isEmpty()){
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/ui_-42-128.png"),"Foto 1");
    ui->lwFotos->addItem(item);
    foto_1=openPicture(dataList_monitoreo.value(4).toString());
  }
  if(!dataList_monitoreo.value(5).toString().isEmpty()){
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/ui_-42-128.png"),"Foto 2");
    ui->lwFotos->addItem(item);
    foto_2=openPicture(dataList_monitoreo.value(5).toString());
  }else{
    foto_2=QImage(":/img/default.png");

  }
  if(!dataList_monitoreo.value(6).toString().isEmpty()){
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/ui_-42-128.png"),"Foto 3");
    ui->lwFotos->addItem(item);
    foto_3=openPicture(dataList_monitoreo.value(6).toString());
  }else{
    foto_3=QImage(":/img/default.png");
  }

  QListWidgetItem *selectedItem=ui->lwFotos->item(0);
  ui->lwFotos->setCurrentItem(selectedItem);
  //coordenas}
  ui->dsbEste->setValue(dataList_monitoreo.value(8).toDouble());
  ui->dsbNorte->setValue(dataList_monitoreo.value(9).toDouble());
  ui->dsbCota->setValue(dataList_monitoreo.value(10).toDouble());
  //descripcion del punto
  ui->txtDesc_punto->setText(dataList_monitoreo.value(11).toString());
  ui->txtDesc_punto->setToolTip(dataList_monitoreo.value(11).toString());


  //datos de campo
  ui->dsbPh->setValue(dataList_monitoreo.value(13).toDouble());
  ui->dsbTemp->setValue(dataList_monitoreo.value(14).toDouble());
  ui->dsbOd->setValue(dataList_monitoreo.value(15).toDouble());
  ui->dsbCond->setValue(dataList_monitoreo.value(16).toDouble());
}

void MainWindow::cleanControls()
{
  ui->txtEstacion->clear();
  ui->deFecha->setDate(QDate::currentDate());
  ui->teHora->setTime(QTime::currentTime());
  ui->txtDescripcion->clear();
  ui->lwFotos->clear();
  ui->dsbPh->setValue(0);
  ui->dsbTemp->setValue(0);
  ui->dsbOd->setValue(0);
  ui->dsbCond->setValue(0);
  ui->dsbEste->setValue(0);
  ui->dsbNorte->setValue(0);
  ui->dsbCota->setValue(0);
  ui->txtDesc_punto->clear();
  //  defaultImage();
}

void MainWindow::defaultImage()
{
  if(dataList_2.isEmpty()){
    QPixmap defaultImage(":/img/default.png");
    ui->lblfoto->setPixmap(defaultImage);
  }

}

QImage MainWindow::openPicture(QString f)
{
  QFile file(f);
  if(!file.open(QFile::ReadOnly)){
    return QImage();
  }
  QImage image(file.fileName());
  return image;
}

void MainWindow::showFotoToControl(QListWidgetItem *item)
{
  //  QPixmap pixMap;
  if(item->data(Qt::DisplayRole).toString()=="Foto 1"){
    //    pixMap.loadFromData(foto_1);
    ui->lblfoto->setPixmap(QPixmap::fromImage(foto_1));
    ui->actionGuardar_foto->setEnabled(true);
    ui->actionGuardar_foto_como->setEnabled(true);
  }
  if(item->data(Qt::DisplayRole).toString()=="Foto 2"){
    //    pixMap.loadFromData(foto_2);
    ui->lblfoto->setPixmap(QPixmap::fromImage(foto_2));
    ui->actionGuardar_foto->setEnabled(true);
    ui->actionGuardar_foto_como->setEnabled(true);
  }
  if(item->data(Qt::DisplayRole).toString()=="Foto 3"){
    //    pixMap.loadFromData(foto_3);
    ui->lblfoto->setPixmap(QPixmap::fromImage(foto_3));
    ui->actionGuardar_foto->setEnabled(true);
    ui->actionGuardar_foto_como->setEnabled(true);
  }
}

QPaintEngine *MainWindow::paintEngine() const
{
  return QWidget::paintEngine();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  QEasySettings::writeSettings("w_setting","w_pos_geometry",this->geometry());
  if(cboTemas->currentText().compare("Tema claro")==0)
    QEasySettings::writeStyle(QEasySettings::Style::lightFusion);
  else
    QEasySettings::writeStyle(QEasySettings::Style::darkFusion);
  event->accept();
}

void MainWindow::on_cboMeses_activated(int index)
{
  Q_UNUSED(index)

  loadDataEstMonitoreo();
  if(dataList_2.isEmpty()){
    cleanControls();
    ui->actionGuardar_foto->setDisabled(true);
    ui->actionGuardar_foto_como->setDisabled(true);
    defaultImage();
  }
}

void MainWindow::on_cboAnios_activated(int index)
{
  Q_UNUSED(index)

  loadDataEstMonitoreo();
  if(dataList_2.isEmpty()){
    cleanControls();
    ui->actionGuardar_foto->setDisabled(true);
    ui->actionGuardar_foto_como->setDisabled(true);
    defaultImage();
  }
}

void MainWindow::on_actionActualizar_datos_triggered()
{
  QVariantList data=bLayer.selectData(dataList.key(ui->cboGrupo->currentText()),
                                        BussinesLayer::GPO_MINERO);
  NuevoDialog *dlgEditGrupo=new NuevoDialog(NuevoDialog::UPDATE_GPO ,data,this);
  dlgEditGrupo->setWindowTitle("Editar datos - Grupo o compañía minera");
  if(dlgEditGrupo->exec()==QDialog::Accepted){
    ui->cboGrupo->clear();
    loadGpoMinerolist();
    ui->cboUnidad->clear();
    loadDataListCliente();

  }

}

void MainWindow::on_actionEditar_datos_unidad_minera_triggered()
{
  QVariantList data=bLayer.selectData(dataListCliente.key(ui->cboUnidad->currentText()),BussinesLayer::CLIENTE);
  NuevoDialog *dlgEditUnidad=new NuevoDialog(NuevoDialog::UPDATE_UNIDAD ,data,this);
  dlgEditUnidad->setWindowTitle("Editar datos - Unidad minera");
  if(dlgEditUnidad->exec()==QDialog::Accepted){
    ui->cboUnidad->clear();
    loadDataListCliente();

  }
}


void MainWindow::on_actioneditar_datos_monitoreo_triggered()
{
  EditDataDialog *editDialog=new EditDataDialog(this);
  editDialog->setWindowTitle(qApp->applicationName().append(" - Editar información"));

  if(editDialog->exec()==QDialog::Accepted){
    ui->lwEstaciones->clear();
    loadDataEstMonitoreo();
    haveData();
  }

}

void MainWindow::on_lwEstaciones_itemSelectionChanged()
{
  datosMonitoreo();
}


void MainWindow::on_lwFotos_itemSelectionChanged()
{
  showFotoToControl(ui->lwFotos->currentItem());

}
MainWindow *MainWindow::getInstance(){
  if(!instance)
    instance=new MainWindow();
  return instance;
}

void MainWindow::haveData()
{
  dataList.isEmpty() ? ui->actionActualizar_datos->setDisabled(true) : ui->actionActualizar_datos->setEnabled(true);
  dataList.isEmpty() ? ui->toolButton_2->setDisabled(true) : ui->toolButton_2->setEnabled(true);
  dataListCliente.isEmpty() ? ui->actionEditar_datos_unidad_minera->setDisabled(true) : ui->actionEditar_datos_unidad_minera->setEnabled(true);
  dataListCliente.isEmpty() ? ui->actionNuevo_punto_de_monitoreo->setDisabled(true) : ui->actionNuevo_punto_de_monitoreo->setEnabled(true);
  dataList_2.isEmpty() ? ui->actioneditar_datos_monitoreo->setDisabled(true) : ui->actioneditar_datos_monitoreo->setEnabled(true);
  dataList_2.isEmpty() ? ui->cboAnios->setDisabled(true) : ui->cboAnios->setEnabled(true);
  dataList_2.isEmpty() ? ui->cboMeses->setDisabled(true) : ui->cboMeses->setEnabled(true);

}

