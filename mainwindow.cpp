#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
  //  QPixmap defaultImage(":/img/camera.png");
  //  ui->lblfoto->setPixmap(defaultImage);
  loadGpoMinerolist();
  ui->deFecha->setDate(QDate::currentDate());
  ui->teHora->setTime(QTime::currentTime());
  //  loadDataListCliente();
  setUpBusqueda();
  ui->dePorFecha->setDate(QDate::currentDate());
  setCompleter();
  //foto


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
  on_cboUnidad_activated(ui->cboUnidad->currentIndex());
}

void MainWindow::loadDataListCliente()
{

  dataListCliente=bLayer.gpoMineroList(BussinesLayer::CLIENTE,dataList.key(ui->cboGrupo->currentText()));
  if(dataListCliente.isEmpty()){
    //    QMessageBox::critical(this,qApp->applicationName(),"Error al cargar los datos\n"+
    //                                                           bLayer.errorMessage());
    return;
  }
  ui->cboUnidad->addItems(dataListCliente.values());

}

void MainWindow::setCompleter()
{
  completer=new QCompleter(bLayer.completerList(),this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtPorNombre->setCompleter(completer);

}


//int MainWindow::getIdGrupo(QString name)
//{
//  return dataList.key(name);
//}

void MainWindow::on_toolButton_clicked()
{
  nuevoFrm=new NuevoDialog(NuevoDialog::GRUPO,this);
  nuevoFrm->setWindowTitle(tr("Nuevo consorcio o grupo minero"));
  if(nuevoFrm->exec()==QDialog::Accepted){
    ui->cboGrupo->clear();
    loadGpoMinerolist();
  }
}

void MainWindow::on_toolButton_2_clicked()
{
  nuevoFrm=new NuevoDialog(NuevoDialog::UNIDAD, this);
  nuevoFrm->setWindowTitle(tr("Nueva unidad minera"));
  nuevoFrm->exec();
}

void MainWindow::on_cboGrupo_activated(int index)
{
  Q_UNUSED(index)
  ui->cboUnidad->clear();
  loadDataListCliente();
  on_cboUnidad_activated(ui->cboUnidad->currentIndex());

}

void MainWindow::setUpBusqueda()
{
  ui->rbPorFecha->setChecked(true);
  ui->txtPorNombre->setEnabled(false);
}


void MainWindow::on_rbPorFecha_clicked()
{
  ui->dePorFecha->setEnabled(true);
  ui->txtPorNombre->setEnabled(false);
  ui->txtPorNombre->clear();
}


void MainWindow::on_rbPorNombre_clicked(bool checked)
{
  ui->txtPorNombre->setEnabled(checked);
  ui->dePorFecha->setEnabled(false);
  ui->txtPorNombre->clear();
  ui->txtPorNombre->setFocus(Qt::OtherFocusReason);
}


void MainWindow::on_actionNuevo_punto_de_monitoreo_triggered()
{
  nuevaEstFrm=new NuevaEstMonitoreoDialog(this);
  if(nuevaEstFrm->exec()==QDialog::Accepted)
    on_cboUnidad_activated(ui->cboUnidad->currentIndex());
}

void MainWindow::on_toolButton_3_clicked()
{
  db.getConection();
  QSqlQuery qry;
  qry.prepare("SELECT foto_1 FROM datos_monitoreo where codigo_estacion=?");
  qry.addBindValue("P-08");
  if(!qry.exec()){
    QMessageBox::critical(this,qApp->applicationName(),
                          "Error\n"+qry.lastError().text());
    return;
  }
  qry.next();
  QByteArray imagen=qry.value(0).toByteArray();
  QPixmap pixMap;
  pixMap.loadFromData(imagen);
  ui->lblfoto->setPixmap(pixMap.scaled(ui->lblfoto->size()));
  qDebug()<<imagen.size();
  qry.finish();
  db.closeConection();
}

void MainWindow::on_cboUnidad_activated(int index)
{
  Q_UNUSED(index)
//  QStringList lista;
  ui->lwEstaciones->clear();
  QHash<int,QString> dataList=bLayer.selectCodEstacion(
    dataListCliente.key(ui->cboUnidad->currentText()),ui->dePorFecha->date().toString());
//  lista=dataList.values();
  /*for (int i=0;i<dataList.count();++i ) {
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/camera.png"),dataList.values().value(i));
    ui->lwEstaciones->addItem(item);
  }*/
  ui->lwEstaciones->addItems(dataList.values());
  qDebug()<<dataList.values();
}


void MainWindow::on_dePorFecha_userDateChanged(const QDate &date)
{
  ui->lwEstaciones->clear();
  QHash<int,QString> dataList=bLayer.selectCodEstacion(
    dataListCliente.key(ui->cboUnidad->currentText()),date.toString());
  ui->lwEstaciones->addItems(dataList.values());
}

