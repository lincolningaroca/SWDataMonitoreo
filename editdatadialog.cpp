#include "ui_editdatadialog.h"
#include "editdatadialog.h"

#include <QDebug>
#include <QMessageBox>
#include "desc_pdialog.h"
#include "fotodialog.h"


EditDataDialog::EditDataDialog(QWidget *parent) :
  QDialog(parent), ui(new Ui::EditDataDialog)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
  loadGpoMinerolist();
  loadDataListCliente();

  dataModel();
  setUpTableView();

  if(dataListCliente.isEmpty() || model->rowCount()==0)
    manageControls(1);
  else
    manageControls(2);

  //  QObject::connect(ui->tableView->selectionModel(),&QItemSelectionModel::currentChanged,
  //                   this,&EditDataDialog::datosMonitoreo);
  QObject::connect(ui->lineEdit_2,&SWCustomTxt::clicked,this,[&](){

    FotoDialog *fDialog=new FotoDialog(imagen_1,this);
    fDialog->exec();
  });
  QObject::connect(ui->lineEdit_3,&SWCustomTxt::clicked,this,[&](){
    if(!list.value(5).toString().isEmpty()){
      FotoDialog *fDialog=new FotoDialog(imagen_2,this);
      fDialog->exec();
    }
  });
  QObject::connect(ui->lineEdit_4,&SWCustomTxt::clicked,this,[&](){
    if(!list.value(6).toString().isEmpty()){
      FotoDialog *fDialog=new FotoDialog(imagen_3,this);
      fDialog->exec();
    }
  });
  setUpToolBtnClear();
  ui->dateEdit->setDate(QDate::currentDate());
  ui->timeEdit->setTime(QTime::currentTime());

}

EditDataDialog::~EditDataDialog()
{
  delete ui;
}

void EditDataDialog::loadGpoMinerolist()
{
  dataList=bLayer.gpoMineroList(BussinesLayer::GPO_MINERO);
  //  if(dataList.isEmpty()){
  ////    QMessageBox::critical(this,qApp->applicationName(),"Error al cargar los datos\n"+
  ////                                                           bLayer.errorMessage());
  //    return;
  //  }

  ui->cboGrupo->addItems(dataList.values());
}

void EditDataDialog::loadDataListCliente()
{
  //  dataListCliente.clear();
  dataListCliente=bLayer.gpoMineroList(BussinesLayer::CLIENTE,
                                         dataList.key(ui->cboGrupo->currentText()));
  if(dataListCliente.isEmpty())
    manageControls(1);
  else
    manageControls(2);
  ui->cboUnidad->addItems(dataListCliente.values());

}

void EditDataDialog::datosMonitoreo()
{
  int nro=bLayer.nro(model->index(ui->twEstaciones->currentIndex().row(),0).data().toInt());
  list=bLayer.dataEstMonitoreo(nro);
  if(list.isEmpty()){
    QMessageBox::information(this,qApp->applicationName(),"no hay datos");
    return;
  }
  ui->lineEdit->setText(list.value(0).toString());
  ui->dateEdit->setDate(list.value(1).toDate());
  ui->timeEdit->setTime(list.value(2).toTime());
  ui->plainTextEdit->setPlainText(list.value(3).toString());

  if(!list.value(4).toString().isEmpty()){
    ui->lineEdit_2->setText("Foto 1");
    imagen_1=openPicture(list.value(4).toString());
    //    oldPath_1=list.value(4).toString();
  }
  //  else
  //    ui->lineEdit_2->clear();
  if(!list.value(5).toString().isEmpty()){
    ui->lineEdit_3->setText("Foto 2");
    imagen_2=openPicture(list.value(5).toString());
    //    oldPath_2=list.value(5).toString();
  }
  else
    ui->lineEdit_3->clear();
  if(!list.value(6).toString().isEmpty()){
    ui->lineEdit_4->setText("Foto 3");
    imagen_3=openPicture(list.value(6).toString());;
    //    oldPath_3=list.value(6).toString();
  }
  else
    ui->lineEdit_4->clear();

  ui->dsbPh->setValue(list.value(13).toDouble());
  ui->dsbTemp->setValue(list.value(14).toDouble());
  ui->dsbOd->setValue(list.value(15).toDouble());
  ui->dsbCond->setValue(list.value(16).toDouble());
  ui->dsbEste->setValue(list.value(8).toDouble());
  ui->dsbNorte->setValue(list.value(9).toDouble());
  ui->dsbCota->setValue(list.value(10).toDouble());
}

//void EditDataDialog::on_txtPath1_returnPressed()
//{
//  qDebug()<<"presionaste el control";
//}

void EditDataDialog::on_btnCancelar_clicked()
{
  accept();
}

void EditDataDialog::on_cboGrupo_activated(int index)
{
  Q_UNUSED(index)
  ui->cboUnidad->clear();
  loadDataListCliente();
  dataModel();
}

void EditDataDialog::on_cboUnidad_activated(int index)
{
  Q_UNUSED(index);
  //  model->clear();
  //  cleanData();
  dataModel();

}
void EditDataDialog::dataModel()
{
  model=new QSqlQueryModel(this);
  int id=dataListCliente.key(ui->cboUnidad->currentText());
  model=bLayer.data(id);
  if(model->rowCount()==0){
    manageControls(1);
  }else{
    manageControls(2);
  }

  ui->twEstaciones->setModel(model);
  if(model->rowCount()!=0){
    ui->twEstaciones->selectRow(0);
    datosMonitoreo();
  }

  QObject::connect(ui->twEstaciones->selectionModel(),&QItemSelectionModel::currentChanged,this,
                   &EditDataDialog::datosMonitoreo);
  //  datosMonitoreo();
}

void EditDataDialog::manageControls(int op)
{
  if(op==1){
    //    ui->twEstaciones->setColumnCount(0);
    ui->twEstaciones->setDisabled(true);
    ui->lineEdit->setDisabled(true);
    ui->dateEdit->setDisabled(true);
    ui->timeEdit->setDisabled(true);
    ui->plainTextEdit->setDisabled(true);
    ui->groupBox_2->setDisabled(true);
    ui->groupBox_4->setDisabled(true);
    ui->groupBox_5->setDisabled(true);
    ui->btnEliminar->setDisabled(true);
    ui->btnGuardar->setDisabled(true);
    ui->label_3->setDisabled(true);
    ui->label_4->setDisabled(true);
    ui->label_5->setDisabled(true);
    ui->label_16->setDisabled(true);

  }else{
    ui->twEstaciones->setEnabled(true);
    ui->lineEdit->setEnabled(true);
    ui->dateEdit->setEnabled(true);
    ui->timeEdit->setEnabled(true);
    ui->plainTextEdit->setEnabled(true);
    ui->groupBox_2->setEnabled(true);
    ui->groupBox_4->setEnabled(true);
    ui->groupBox_5->setEnabled(true);
    ui->btnGuardar->setEnabled(true);
    ui->btnEliminar->setEnabled(true);
    ui->label_3->setEnabled(true);
    ui->label_4->setEnabled(true);
    ui->label_5->setEnabled(true);
    ui->label_16->setEnabled(true);
  }
}

QImage EditDataDialog::openPicture(QString f)
{
  QFile file(f);
  if(!file.open(QFile::ReadOnly)){
    return QImage();
  }
  QImage image(file.fileName());
  return image;
}

void EditDataDialog::setUpTableView()
{
  model->setHeaderData(1,Qt::Horizontal,"CODIGO DE ESTACION");
  model->setHeaderData(2,Qt::Horizontal,"FECHA");
  ui->twEstaciones->hideColumn(0);
  ui->twEstaciones->hideColumn(3);
  ui->twEstaciones->setColumnWidth(1,150);
  if(model->rowCount()!=0)
    ui->twEstaciones->selectRow(0);
}
void EditDataDialog::on_btnEliminar_clicked()
{
  QVariant idEstacion=model->index(ui->twEstaciones->currentIndex().row(),0).data();
  QString codEstacion=list.value(0).toString();

  QMessageBox msgBox;
  msgBox.setText(QString("Seguro que desea eliminar este registro:%1").arg(
    "<p style=\"color:#CF1F25;\"><b>"+codEstacion+"</b></p>"));
  msgBox.setIcon(QMessageBox::Question);
  msgBox.addButton(new QPushButton("Eliminar registro"),QMessageBox::AcceptRole);
  msgBox.addButton(new QPushButton("Cancelar"),QMessageBox::RejectRole);
  if(msgBox.exec()==QMessageBox::RejectRole)
    return;

  QVariantList param;
  param.append(idEstacion);

  if(!bLayer.monitoreoMineroAction(param,BussinesLayer::DELETE)){
    QMessageBox::critical(this,qApp->applicationName(),
                          "Error al eliminar los datos.\n"+
                            bLayer.errorMessage()+"\n"+bLayer.errorCode());
    return;
  }
  QMessageBox::information(this,qApp->applicationName(),"Registro eliminado");
  //  accept();
  //  cleanData();
  dataModel();
  datosMonitoreo();

}

void EditDataDialog::on_btnGuardar_clicked()
{
  QVariantList datos;
  datos.append(ui->lineEdit->text().toUpper());
  datos.append(ui->dateEdit->date());
  datos.append(ui->timeEdit->time());
  datos.append(ui->plainTextEdit->toPlainText());
  if(!newPath_1.isEmpty()){
    datos.append(newPath_1);
    QFile::remove(list.value(4).toString());
  }else{
    datos.append(list.value(4).toString());
  }
  if(!newPath_2.isEmpty()){
    if(!list.value(5).toString().isEmpty()){
      datos.append(newPath_2);
      QFile::remove(list.value(5).toString());
    }
    datos.append(newPath_2);
  }else{
    if(!ui->lineEdit_3->text().isEmpty())
      datos.append(list.value(5).toString());
    else{
      if(!list.value(5).toString().isEmpty()){
        QFile::remove(list.value(5).toString());
        datos.append(QString());
      }
      else
        datos.append(QString());
    }
  }
  if(!newPath_3.isEmpty()){
    if(!list.value(6).toString().isEmpty()){
      datos.append(newPath_3);
      QFile::remove(list.value(6).toString());
    }
    datos.append(newPath_3);
  }else{
    if(!ui->lineEdit_4->text().isEmpty())
      datos.append(list.value(6).toString());
    else{
      if(!list.value(6).toString().isEmpty()){
        QFile::remove(list.value(6).toString());
        datos.append(QString());
      }
      else
        datos.append(QString());
    }
  }
  datos.append(dataListCliente.key(ui->cboUnidad->currentText()));
  datos.append(ui->dsbEste->value());
  datos.append(ui->dsbNorte->value());
  datos.append(ui->dsbCota->value());
  datos.append(desc_punto);
  datos.append(model->index(ui->twEstaciones->currentIndex().row(),0).data().toInt());

  if(ui->lineEdit->text().simplified().isEmpty()){
    QMessageBox::warning(this,qApp->applicationName(),"El campo código de estación es requerido.");
    ui->lineEdit->selectAll();
    ui->lineEdit->setFocus(Qt::OtherFocusReason);
    return;
  }

  if(!bLayer.monitoreoMineroAction(datos,BussinesLayer::UPDATE)){
    QMessageBox::critical(this,qApp->applicationName(),
                          "Error al actualizar los datos.\n"+
                            bLayer.errorMessage()+"\n"+bLayer.errorCode());
    return;

  }
  QVariantList datos_campo;
  datos_campo.append(ui->dsbPh->value());
  datos_campo.append(ui->dsbTemp->value());
  datos_campo.append(ui->dsbOd->value());
  datos_campo.append(ui->dsbCond->value());
  datos_campo.append(bLayer.nro(model->index(ui->twEstaciones->currentIndex().row(),0).data().toInt()));
  datos_campo.append(model->index(ui->twEstaciones->currentIndex().row(),0).data().toInt());

  if(!bLayer.parametroAction(datos_campo,BussinesLayer::UPDATE)){
    QMessageBox::critical(this,qApp->applicationName(),
                          "Error al actualizar los datos.\n"+
                            bLayer.errorMessage()+"\n"+bLayer.errorCode());
    return;

  }
  if(!newPath_1.isEmpty()){
    QFile::copy(ui->lineEdit_2->text(),newPath_1);
  }
  if(!newPath_2.isEmpty()){
    QFile::copy(ui->lineEdit_3->text(),newPath_2);
  }
  if(!newPath_3.isEmpty()){
    QFile::copy(ui->lineEdit_4->text(),newPath_3);
  }




  QMessageBox::information(this,qApp->applicationName(),"Datos guardados.");
  newPath_1.clear();
  newPath_2.clear();
  newPath_3.clear();
  //  accept();
  //  cleanData();
  dataModel();
  datosMonitoreo();
  //  qDebug()<<bLayer.nro(dataListCliente.key(ui->cboUnidad->currentText()));

}

void EditDataDialog::on_toolButton_clicked()
{

  QString fileName=QFileDialog::getOpenFileName(this,"Cargar una imagen.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty())
    return;
  QFileInfo info(fileName);
  QString absolutePath;
  absolutePath.append(bLayer.relativePath());
  absolutePath.append("/");
  absolutePath.append(info.fileName());
  newPath_1=absolutePath;
  ui->lineEdit_2->setText(fileName);
}


void EditDataDialog::on_pushButton_clicked()
{
  Desc_pDialog *desc_dialog;
  if(list.value(11).toString().isEmpty())
    desc_dialog=new Desc_pDialog(2,desc_punto);
  else
    desc_dialog=new Desc_pDialog(2,list.value(11).toString());

  if(desc_dialog->exec()==QDialog::Accepted)
    desc_punto=desc_dialog->desc();

}


void EditDataDialog::on_toolButton_2_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,"Cargar una imagen.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty())
    return;

  QFileInfo info(fileName);
  QString absolutePath;
  absolutePath.append(bLayer.relativePath());
  absolutePath.append("/");
  absolutePath.append(info.fileName());
  newPath_2=absolutePath;
  ui->lineEdit_3->setText(fileName);

}


void EditDataDialog::on_toolButton_3_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,"Cargar una imagen.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty())
    return;

  QFileInfo info(fileName);
  QString absolutePath;
  absolutePath.append(bLayer.relativePath());
  absolutePath.append("/");
  absolutePath.append(info.fileName());
  newPath_3=absolutePath;
  ui->lineEdit_4->setText(fileName);
}
void EditDataDialog::setUpToolBtnClear()
{
  QAction *closeAction=ui->lineEdit_2->addAction(QIcon(":/img/1916591.png"),
                                                   QLineEdit::TrailingPosition);
  closeAction->setToolTip("Quitar foto");
  connect(closeAction,&QAction::triggered,this,[=](){
    QMessageBox::warning(this,qApp->applicationName(),"No puede quitar ésta imagen.\n"
                                                        "La primera imagen siempre es requerida.\n"
                                                        "Recuerde que tiene que guardar los datos con una imagen como minimo.");
    return;
    //    ui->lineEdit_2->clear();

  });

  QAction *closeAction1=ui->lineEdit_3->addAction(QIcon(":/img/1916591.png"),
                                                    QLineEdit::TrailingPosition);
  closeAction1->setToolTip("Quitar foto");
  connect(closeAction1,&QAction::triggered,this,[&](){

    if(ui->lineEdit_3->text().isEmpty()){
      return;
    }
    QMessageBox mBox;
    mBox.setText("Seguro que desea quitar ésta imagen?");
    mBox.setIcon(QMessageBox::Question);
    mBox.addButton(new QPushButton("Quitar imagen"),QMessageBox::AcceptRole);
    mBox.addButton(new QPushButton("Cancelar"),QMessageBox::RejectRole);
    if(mBox.exec()==QMessageBox::RejectRole)
      return;
    if(!newPath_2.isEmpty())
      newPath_2.clear();
    ui->lineEdit_3->clear();

  });

  QAction *closeAction2=ui->lineEdit_4->addAction(QIcon(":/img/1916591.png"),
                                                    QLineEdit::TrailingPosition);
  closeAction2->setToolTip("Quitar foto");
  connect(closeAction2,&QAction::triggered,this,[=](){
    if(ui->lineEdit_4->text().isEmpty()){
      return;
    }
    QMessageBox mBox;
    mBox.setText("Seguro que desea quitar ésta imagen?");
    mBox.setIcon(QMessageBox::Question);
    mBox.addButton(new QPushButton("Quitar imagen"),QMessageBox::AcceptRole);
    mBox.addButton(new QPushButton("Cancelar"),QMessageBox::RejectRole);
    if(mBox.exec()==QMessageBox::RejectRole)
      return;
    if(!newPath_3.isEmpty())
      newPath_3.clear();
    ui->lineEdit_4->clear();

  });

}

QPaintEngine *EditDataDialog::paintEngine() const
{
  return QWidget::paintEngine();

}

void EditDataDialog::closeEvent(QCloseEvent *event)
{
  accept();
  event->accept();

}

