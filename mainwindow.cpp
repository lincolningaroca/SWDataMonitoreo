#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  QPixmap defaultImage(":/img/logoEmpresa.png");
  ui->lblfoto->setPixmap(defaultImage);
  ui->lblfoto->setScaledContents(true);
  ui->lblfoto->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  loadGpoMinerolist();
  ui->deFecha->setDate(QDate::currentDate());
  ui->teHora->setTime(QTime::currentTime());
  loadMesesAnios();
  loadCboTemas();
  loadDataEstMonitoreo();

  loadSettings();



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
  loadDataListCliente();
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
  dataList_2.clear();
  dataList_2=bLayer.selectCodEstacion(ui->cboAnios->currentData(Qt::DisplayRole).toInt(),
                                        meses.key(ui->cboMeses->currentText()),
                                        dataListCliente.key(ui->cboUnidad->currentText()));

  //  ui->lwEstaciones->addItems(dataList_2.values());
  QStringList l=dataList_2.values();
  for(int i=0;i<dataList_2.count();++i){
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/ui-11-128.png"),l.value(i));
    ui->lwEstaciones->addItem(item);
  }



}

void MainWindow::loadCboTemas()
{
  cboTemas=new QComboBox(this);
  cboTemas->addItem("Tema claro");
  cboTemas->addItem("Tema oscuro");
  ui->toolBar->addWidget(cboTemas);
  QObject::connect(cboTemas,&QComboBox::activated,this,[&](){
    if(cboTemas->currentIndex()==0){
      QEasySettings::setStyle(QEasySettings::Style::lightFusion);
      QPixmap defaultImage(":/img/logoEmpresa.png");
      ui->lblfoto->setPixmap(defaultImage);
      //      ui->lblfoto->setScaledContents(true);
      //      ui->lblfoto->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    }else{
      QEasySettings::setStyle(QEasySettings::Style::darkFusion);
      QPixmap defaultImage(":/img/logoEmpresa_1.png");
      ui->lblfoto->setPixmap(defaultImage);
      //      ui->lblfoto->setScaledContents(true);
      //      ui->lblfoto->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    }
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
  ui->lwEstaciones->clear();
  loadDataEstMonitoreo();

}


void MainWindow::on_actionNuevo_punto_de_monitoreo_triggered()
{
  nuevaEstFrm=new NuevaEstMonitoreoDialog(this);
  nuevaEstFrm->setWindowTitle(qApp->applicationName().append(" - Nuevo"));
  if(nuevaEstFrm->exec()==QDialog::Accepted){
    ui->lwEstaciones->clear();
    loadDataEstMonitoreo();
  }
}



void MainWindow::on_cboUnidad_activated(int index)
{
  Q_UNUSED(index)
  ui->lwEstaciones->clear();
  loadDataEstMonitoreo();
  //    qDebug()<<dataListCliente.key(ui->cboUnidad->currentText());
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
  QVariantList dataList=bLayer.dataEstMonitoreo(nro);
  ui->txtEstacion->setText(dataList.value(0).toString());
  ui->deFecha->setDate(dataList.value(1).toDate());
  ui->teHora->setTime(dataList.value(2).toTime());
  ui->txtDescripcion->setPlainText(dataList.value(3).toString());
  ui->lwFotos->clear();

  if(dataList.value(4).toByteArray().size()!=0){
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/ui_-42-128.png"),"Foto 1");
    ui->lwFotos->addItem(item);
    foto_1=dataList.value(4).toByteArray();
  }
  if(dataList.value(5).toByteArray().size()!=0){
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/ui_-42-128.png"),"Foto 2");
    ui->lwFotos->addItem(item);
    foto_2=dataList.value(5).toByteArray();
  }else{
    foto_2=QByteArray(":/img/logoEmpresa.png");

  }
  if(dataList.value(6).toByteArray().size()!=0){
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/ui_-42-128.png"),"Foto 3");
    ui->lwFotos->addItem(item);
    foto_3=dataList.value(5).toByteArray();
  }else{
    foto_3=QByteArray(":/img/logoEmpresa.png").constData();
  }

  ui->dsbPh->setValue(dataList.value(9).toDouble());
  ui->dsbTemp->setValue(dataList.value(10).toDouble());
  ui->dsbOd->setValue(dataList.value(11).toDouble());
  ui->dsbCond->setValue(dataList.value(12).toDouble());

}

QPaintEngine *MainWindow::paintEngine() const
{
  return MainWindow::paintEngine();
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
  ui->lwEstaciones->clear();
  dataList_2.clear();
  dataList_2=bLayer.selectCodEstacion(ui->cboAnios->currentData(Qt::DisplayRole).toInt(),
                                        meses.key(ui->cboMeses->currentText()),
                                        dataListCliente.key(ui->cboUnidad->currentText()));
  //  ui->lwEstaciones->addItems(dataList_2.values());
  QStringList l=dataList_2.values();
  for(int i=0;i<dataList_2.count();++i){
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/ui-11-128.png"),l.value(i));
    ui->lwEstaciones->addItem(item);
  }
}

void MainWindow::on_cboAnios_activated(int index)
{
  Q_UNUSED(index)
  ui->lwEstaciones->clear();
  dataList_2.clear();
  dataList_2=bLayer.selectCodEstacion(ui->cboAnios->currentData(Qt::DisplayRole).toInt(),
                                        meses.key(ui->cboMeses->currentText()),
                                        dataListCliente.key(ui->cboUnidad->currentText()));
  //  ui->lwEstaciones->addItems(dataList_2.values());
  QStringList l=dataList_2.values();
  for(int i=0;i<dataList_2.count();++i){
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/Lab_tube.png"),l.value(i));
    ui->lwEstaciones->addItem(item);
  }
}


void MainWindow::on_lwEstaciones_itemClicked(QListWidgetItem *item)
{

  datosMonitoreo();
}

void MainWindow::on_lwFotos_itemClicked(QListWidgetItem *item)
{
  QPixmap pixMap;
  if(item->data(Qt::DisplayRole).toString()=="Foto 1"){
    pixMap.loadFromData(foto_1);
    ui->lblfoto->setPixmap(pixMap);
  }
  if(item->data(Qt::DisplayRole).toString()=="Foto 2"){
    pixMap.loadFromData(foto_2);
    ui->lblfoto->setPixmap(pixMap);
  }
  if(item->data(Qt::DisplayRole).toString()=="Foto 3"){
    pixMap.loadFromData(foto_3);
    ui->lblfoto->setPixmap(pixMap);
  }
}

void MainWindow::on_actionActualizar_datos_triggered()
{
  QVariantList data=bLayer.selectData(dataList.key(ui->cboGrupo->currentText()),
                                        BussinesLayer::GPO_MINERO);
  NuevoDialog *dlgEditGrupo=new NuevoDialog(NuevoDialog::UPDATE_GPO ,data,this);
  dlgEditGrupo->setWindowTitle("Editar datos - consorcio minero");
  if(dlgEditGrupo->exec()==QDialog::Accepted){
    ui->cboGrupo->clear();
    loadGpoMinerolist();
    ui->cboUnidad->clear();
    loadDataListCliente();
  }

}

void MainWindow::on_actionEditar_datos_unidad_minera_triggered()
{
  NuevoDialog *dlgEditUnidad=new NuevoDialog(NuevoDialog::UPDATE_UNIDAD ,QVariantList(),this);
  dlgEditUnidad->setWindowTitle("Editar datos - unidad minera");
  dlgEditUnidad->exec();
}


void MainWindow::on_actioneditar_datos_monitoreo_triggered()
{
  EditDataDialog *editDialog=new EditDataDialog(this);
  editDialog->exec();
}

