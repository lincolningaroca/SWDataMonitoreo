#include "nuevaestmonitoreodialog.h"
#include "ui_nuevaestmonitoreodialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "desc_pdialog.h"

NuevaEstMonitoreoDialog::NuevaEstMonitoreoDialog(QWidget *parent) :
  QDialog(parent),ui(new Ui::NuevaEstMonitoreoDialog)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
  ui->deFecha->setDate(QDate::currentDate());
  ui->teHora->setTime(QTime::currentTime());
  loadGpoMinerolist();
  //  qDebug()<<bLayer.lInsertId();

  ui->btnFoto2->setDisabled(true);
  ui->btnFoto3->setDisabled(true);

  setUpToolBtnClear();
}

NuevaEstMonitoreoDialog::~NuevaEstMonitoreoDialog()
{
  delete ui;
}

void NuevaEstMonitoreoDialog::on_btnGuardar_clicked()
{
  if(ui->txtCodigo->text().simplified().isEmpty()){
    QMessageBox::warning(this,qApp->applicationName(),"El código de estación es requerido.\n");
    ui->txtCodigo->setFocus(Qt::OtherFocusReason);
    return;
  }
  if(ui->txtPath1->text().isEmpty()){
    QMessageBox::warning(this,qApp->applicationName(),"Debe ingresar al menos una foto.\n");
    ui->btnFoto1->setFocus(Qt::OtherFocusReason);
    return;
  }

  QVariantList param;
  param.append(ui->txtCodigo->text().toUpper());
  param.append(ui->deFecha->date());
  param.append(ui->teHora->time());
  param.append(ui->teDescripcion->toPlainText());
  //agregar las tres imagenes

  param.append(pathImage_1);
  param.append(pathImage_2);
  param.append(pathImage_3);


  //  param.append(imagen_3);
  //agreagr el codigo del cliene
  param.append(dataListCliente.key(ui->cboUnidad->currentText()));
  //agregar las coordenadas
  param.append(ui->dsbEste->value());
  param.append(ui->dsbNorte->value());
  param.append(ui->dsbCota->value());
  param.append(desc_punto);


  if(!bLayer.monitoreoMineroAction(param,BussinesLayer::INSERT)){
    if(bLayer.errorCode()=="23503"){
      QMessageBox::warning(this,qApp->applicationName(),
                           "No existe algún registro donde se pueda almacenar esta información.\n\n"
                           "Esto se debe a que no existen datos en el campo, unidad minera.\n"
                           "* salga de ésta ventana y agregue una nueva unidad minera,"
                           "en el botón que se \n  muestra al lado de la lista desplegable"
                           " Unidad minera, del formulario principal.");
      ui->txtCodigo->selectAll();
      ui->txtCodigo->setFocus(Qt::OtherFocusReason);
      return;
    }
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

  QFile::copy(ui->txtPath1->text(),pathImage_1);
  if(!pathImage_2.isEmpty())
    QFile::copy(ui->txtPath2->text(),pathImage_2);
  if(!pathImage_3.isEmpty())
    QFile::copy(ui->txtPath3->text(),pathImage_3);

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

void NuevaEstMonitoreoDialog::setUpToolBtnClear()
{
  QAction *closeAction=ui->txtPath1->addAction(QIcon(":/img/1916591.png"),
                                                 QLineEdit::TrailingPosition);
  connect(closeAction,&QAction::triggered,this,[=](){
    ui->txtPath1->clear();
    ui->txtPath2->clear();
    ui->txtPath3->clear();
  });
  QAction *closeAction1=ui->txtPath2->addAction(QIcon(":/img/1916591.png"),
                                                  QLineEdit::TrailingPosition);
  connect(closeAction1,&QAction::triggered,this,[=](){
    ui->txtPath2->clear();
    ui->txtPath3->clear();
    pathImage_2.clear();
  });
  QAction *closeAction2=ui->txtPath3->addAction(QIcon(":/img/1916591.png"),
                                                  QLineEdit::TrailingPosition);
  connect(closeAction2,&QAction::triggered,this,[=](){
    ui->txtPath3->clear();
    pathImage_3.clear();
  });

}

void NuevaEstMonitoreoDialog::on_cboGrupo_activated(int index)
{
  Q_UNUSED(index)
  ui->cboUnidad->clear();
  loadDataListCliente();
}


void NuevaEstMonitoreoDialog::on_btnFoto1_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,"Cargar una imagen.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty())
    return;
  QFileInfo info(fileName);
  if(QFileInfo::exists(bLayer.relativePath().append("/").append(info.fileName()))){
    QMessageBox::warning(this,qApp->applicationName(),tr("Ya existe una imagen con este nombre:\n %1").arg(
                                                          info.fileName()));
    return;
  }

  //  QFileInfo info(fileName);
  QString absolutePath;
  absolutePath.append(bLayer.relativePath());
  absolutePath.append("/");
  absolutePath.append(info.fileName());
  pathImage_1=absolutePath;
  ui->txtPath1->setText(fileName);

}


void NuevaEstMonitoreoDialog::on_btnCancelar_clicked()
{
  reject();
}


void NuevaEstMonitoreoDialog::on_btnFoto2_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,"Cargar una imagen.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty()){
    pathImage_2="";
    return;
  }
  QFileInfo info(fileName);
  if(QFileInfo::exists(bLayer.relativePath().append("/").append(info.fileName()))){
    QMessageBox::warning(this,qApp->applicationName(),tr("Ya existe una imagen con este nombre:\n %1").arg(
                                                          info.fileName()));
    return;
  };

  QString absolutePath;
  absolutePath.append(bLayer.relativePath());
  absolutePath.append("/");
  absolutePath.append(info.fileName());
  pathImage_2=absolutePath;
  ui->txtPath2->setText(fileName);


}


void NuevaEstMonitoreoDialog::on_btnFoto3_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,"Cargar una imagen.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty()){
    pathImage_3="";
    return;
  }
  QFileInfo info(fileName);
  if(QFileInfo::exists(bLayer.relativePath().append("/").append(info.fileName()))){
    QMessageBox::warning(this,qApp->applicationName(),tr("Ya existe una imagen con este nombre:\n %1").arg(
                                                          info.fileName()));
    return;
  }

  QString absolutePath;
  absolutePath.append(bLayer.relativePath());
  absolutePath.append("/");
  absolutePath.append(info.fileName());
  pathImage_3=absolutePath;
  ui->txtPath3->setText(fileName);
}


void NuevaEstMonitoreoDialog::on_txtPath1_textChanged(const QString &arg1)
{
  if(!arg1.isEmpty()){
    ui->btnFoto2->setEnabled(true);
  }else
    ui->btnFoto2->setDisabled(true);
}


void NuevaEstMonitoreoDialog::on_txtPath2_textChanged(const QString &arg1)
{
  if(!arg1.isEmpty()){
    ui->btnFoto3->setEnabled(true);
  }else
    ui->btnFoto3->setDisabled(true);
}


void NuevaEstMonitoreoDialog::on_pushButton_clicked()
{
  Desc_pDialog *descDialog=new Desc_pDialog(2,desc_punto);
  if(descDialog->exec()==QDialog::Accepted)
    desc_punto=descDialog->desc();
}
