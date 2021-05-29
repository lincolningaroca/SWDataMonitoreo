#include "nuevaestmonitoreodialog.h"
#include "ui_nuevaestmonitoreodialog.h"
#include <QMessageBox>
#include <QFileDialog>

NuevaEstMonitoreoDialog::NuevaEstMonitoreoDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::NuevaEstMonitoreoDialog)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
  ui->deFecha->setDate(QDate::currentDate());
  ui->teHora->setTime(QTime::currentTime());
  loadGpoMinerolist();
  //  qDebug()<<bLayer.lInsertId();
}

NuevaEstMonitoreoDialog::~NuevaEstMonitoreoDialog()
{
  delete ui;
}

void NuevaEstMonitoreoDialog::on_btnGuardar_clicked()
{
  if(ui->txtCodigo->text().isEmpty()){
    QMessageBox::warning(this,qApp->applicationName(),"El codigo de estación es requerido.\n");
    ui->txtCodigo->setFocus(Qt::OtherFocusReason);
    return;
  }
  QVariantList param;
  param.append(ui->txtCodigo->text());
  param.append(ui->deFecha->date());
  param.append(ui->teHora->time());
  param.append(ui->teDescripcion->toPlainText());
  //agregar las tres imagenes
  param.append(imagen_1);
  param.append(imagen_2);
  param.append(imagen_3);
  //agreagr el codigo del cliene
  param.append(dataListCliente.key(ui->cboUnidad->currentText()));


  if(!bLayer.monitoreoMineroAction(param,BussinesLayer::INSERT)){
    //    if(bLayer.errorCode()=="23505"){
    //      QMessageBox::warning(this,qApp->applicationName(),
    //                           "Este código ya esta registrado en la base de datos.\n"
    //                           "Por favor intente con uno nuevo.");
    //      ui->txtCodigo->selectAll();
    //      ui->txtCodigo->setFocus(Qt::OtherFocusReason);
    //      return;
    //    }
    QMessageBox::critical(this,qApp->applicationName(),bLayer.errorMessage());
    return;
  }
  _idEstacion=bLayer.lInsertId();
  QVariantList param_1;
  param_1.append(ui->dsbPh->value());
  param_1.append(ui->dsbTemp->value());
  param_1.append(ui->dsbOd->value());
  param_1.append(ui->dsbCond->value());
  param_1.append(_idEstacion);

  if(!bLayer.parametroAction(param_1,BussinesLayer::INSERT)){
    QMessageBox::critical(this,qApp->applicationName(),"Error al insertar los datos.\n"+
                                                           bLayer.errorMessage());
    return;
  }
  QMessageBox::information(this,qApp->applicationName(),"Datos guardados.");
  //  qDebug()<<bLayer.lInsertId();
  accept();
}

void NuevaEstMonitoreoDialog::loadGpoMinerolist()
{
  dataList=bLayer.gpoMineroList(BussinesLayer::GPO_MINERO);
  ui->cboGrupo->addItems(dataList.values());
  loadDataListCliente();
}

void NuevaEstMonitoreoDialog::loadDataListCliente()
{
  dataListCliente=bLayer.gpoMineroList(BussinesLayer::CLIENTE,dataList.key(ui->cboGrupo->currentText()));
  ui->cboUnidad->addItems(dataListCliente.values());

}

void NuevaEstMonitoreoDialog::on_cboGrupo_activated(int index)
{
  Q_UNUSED(index)
  ui->cboUnidad->clear();
  loadDataListCliente();
}


void NuevaEstMonitoreoDialog::on_btnFoto1_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,"Abrir una foto.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty())
    return;
  QFile file(fileName);
  if(!file.open(QFile::ReadOnly)){
    QMessageBox::critical(this,qApp->applicationName(),
                          "Error al abrir el archivo.\n"+file.errorString());
    return;
  }
  ui->txtPath1->setText(fileName);
  imagen_1=file.readAll();
  file.close();
  file.flush();
  //  qDebug()<<imagen_1.size();

}


void NuevaEstMonitoreoDialog::on_btnCancelar_clicked()
{
  reject();
}


void NuevaEstMonitoreoDialog::on_btnFoto2_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,"Abrir una foto.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty())
    return;
  QFile file(fileName);
  if(!file.open(QFile::ReadOnly)){
    QMessageBox::critical(this,qApp->applicationName(),
                          "Error al abrir el archivo.\n"+file.errorString());
    return;
  }
  ui->txtPath2->setText(fileName);
  imagen_2=file.readAll();
  file.close();
  file.flush();
  //  qDebug()<<imagen_1.size();
}


void NuevaEstMonitoreoDialog::on_btnFoto3_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,"Abrir una foto.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty())
    return;
  QFile file(fileName);
  if(!file.open(QFile::ReadOnly)){
    QMessageBox::critical(this,qApp->applicationName(),
                          "Error al abrir el archivo.\n"+file.errorString());
    return;
  }
  ui->txtPath3->setText(fileName);
  imagen_3=file.readAll();
  file.close();
  file.flush();
  //  qDebug()<<imagen_1.size();
}

