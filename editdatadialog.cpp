#include "editdatadialog.h"
#include "ui_editdatadialog.h"
#include <QDebug>
#include <QMessageBox>
//#include <QSqlQuery>
//#include <QSqlError>
#include "desc_pdialog.h"
#include "fotodialog.h"
#include <QRegularExpression>

EditDataDialog::EditDataDialog(QWidget *parent) :
  QDialog(parent), ui(new Ui::EditDataDialog)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
  ui->btnGuardar->setDefault(true);
  loadGpoMinerolist();
  QStringList titulos;
  titulos<<"ID_ESTACION"<<"CODIGO DE ESTCION"<<"FECHA"<<"ID_CLIENTE";
  ui->twEstaciones->setColumnCount(titulos.count());
  ui->twEstaciones->setHorizontalHeaderLabels(titulos);
  ui->twEstaciones->hideColumn(0);
  ui->twEstaciones->hideColumn(3);

  dataModel();
  if(dataListCliente.isEmpty() || model->rowCount()==0)
    manageControls(1);
  else
    manageControls(2);

  QObject::connect(ui->twEstaciones->selectionModel(),&QItemSelectionModel::currentChanged,
                   this,&EditDataDialog::datosMonitoreo);
  QObject::connect(ui->lineEdit_2,&SWCustomTxt::clicked,this,[&](){
    FotoDialog *fDialog=new FotoDialog(imagen_1,this);
    fDialog->exec();
  });
  QObject::connect(ui->lineEdit_3,&SWCustomTxt::clicked,this,[&](){
    if(imagen_2.size()!=0){
      FotoDialog *fDialog=new FotoDialog(imagen_2,this);
      fDialog->exec();
    }
  });
  QObject::connect(ui->lineEdit_4,&SWCustomTxt::clicked,this,[&](){
    if(imagen_3.size()!=0){
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
  loadDataListCliente();


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
  //  list.clear();
  imagen_1.clear();
  imagen_2.clear();
  imagen_3.clear();
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
  if(list.value(4).toByteArray().size()!=0){
    ui->lineEdit_2->setText("Imagen 1");
    imagen_1=list.value(4).toByteArray();
  }
  else
    ui->lineEdit_2->clear();
  if(list.value(5).toByteArray().size()!=0){
    ui->lineEdit_3->setText("Imagen 2");
    imagen_2=list.value(5).toByteArray();
  }
  else
    ui->lineEdit_3->clear();
  if(list.value(6).toByteArray().size()!=0){
    ui->lineEdit_4->setText("Imagen 3");
    imagen_3=list.value(6).toByteArray();
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
  reject();
}

void EditDataDialog::on_cboGrupo_activated(int index)
{
  Q_UNUSED(index)
  ui->cboUnidad->clear();
  loadDataListCliente();
  //  on_cboUnidad_activated(index);
  cleanData();
  dataModel();
}

void EditDataDialog::on_cboUnidad_activated(int index)
{
  Q_UNUSED(index);
  //  model->clear();
  cleanData();
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

  for(int i=0;i<model->rowCount();++i){
    int rowCount=ui->twEstaciones->rowCount();
    ui->twEstaciones->insertRow(rowCount);
    ui->twEstaciones->setItem(i,0,new QTableWidgetItem(model->index(i,0).data().toString()));
    ui->twEstaciones->setItem(i,1,new QTableWidgetItem(model->index(i,1).data().toString()));
    ui->twEstaciones->setItem(i,2,new QTableWidgetItem(model->index(i,2).data().toString()));
    ui->twEstaciones->setItem(i,3,new QTableWidgetItem(model->index(i,3).data().toString()));
    ui->twEstaciones->setColumnWidth(1,150);
    ui->twEstaciones->hideColumn(0);
    ui->twEstaciones->hideColumn(3);
  }
  QModelIndex index=ui->twEstaciones->model()->index(0,0);
  ui->twEstaciones->setCurrentIndex(index);
  //  ui->twEstaciones->selectionModel()->select(index,QItemSelectionModel::Select);
  datosMonitoreo();
}

void EditDataDialog::cleanData()
{
  for(int i=ui->twEstaciones->rowCount()-1;i>=0;--i){
    ui->twEstaciones->removeRow(i);
  }
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
void EditDataDialog::on_btnEliminar_clicked()
{


}

void EditDataDialog::on_btnGuardar_clicked()
{
  QVariantList datos;
  datos.append(ui->lineEdit->text());
  datos.append(ui->dateEdit->date());
  datos.append(ui->timeEdit->time());
  datos.append(ui->plainTextEdit->toPlainText());
  datos.append(imagen_1);
  datos.append(imagen_2);
  datos.append(imagen_3);
  datos.append(dataListCliente.key(ui->cboUnidad->currentText()));
  datos.append(ui->dsbEste->value());
  datos.append(ui->dsbNorte->value());
  datos.append(ui->dsbCota->value());
  datos.append(desc_punto);
  datos.append(model->index(ui->twEstaciones->currentRow(),0).data().toInt());

  if(ui->lineEdit->text().simplified().isEmpty()){
    QMessageBox::warning(this,qApp->applicationName(),"El campo codigo de estación es requerido.");
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
  datos_campo.append(bLayer.nro(model->index(ui->twEstaciones->currentRow(),0).data().toInt()));
  datos_campo.append(model->index(ui->twEstaciones->currentRow(),0).data().toInt());

  if(!bLayer.parametroAction(datos_campo,BussinesLayer::UPDATE)){
    QMessageBox::critical(this,qApp->applicationName(),
                          "Error al actualizar los datos.\n"+
                            bLayer.errorMessage()+"\n"+bLayer.errorCode());
    return;

  }
  QMessageBox::information(this,qApp->applicationName(),"Datos guardados.");
  accept();
  //  qDebug()<<bLayer.nro(dataListCliente.key(ui->cboUnidad->currentText()));

}


void EditDataDialog::on_toolButton_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,"Cargar una imagen.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty()){
    //    imagen_1=QByteArray();
    return;
  }
  QFileInfo info(fileName);
  if((info.size()/1024)>2048){
    QMessageBox::critical(this,qApp->applicationName(),
                          "El archivo que está intentando guardar es muy grande.\n"
                          "Puede guardar archivos con un máximo de tamaño de 2 MB.");
    return;
  }
  QFile file(fileName);
  if(!file.open(QFile::ReadOnly)){
    QMessageBox::critical(this,qApp->applicationName(),
                          "Error al abrir el archivo.\n"+file.errorString());
    return;
  }
  ui->lineEdit_2->setText(fileName);
  imagen_1=file.readAll();
  file.close();
  file.flush();
}


void EditDataDialog::on_pushButton_clicked()
{
  Desc_pDialog *desc_dialog=new Desc_pDialog(2,list.value(11).toString());

  if(desc_dialog->exec()==QDialog::Accepted)
    desc_punto=desc_dialog->desc();

}


void EditDataDialog::on_toolButton_2_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,"Cargar una imagen.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty()){
    //    imagen_1=QByteArray();
    return;
  }
  QFileInfo info(fileName);
  if((info.size()/1024)>2048){
    QMessageBox::critical(this,qApp->applicationName(),
                          "El archivo que está intentando guardar es muy grande.\n"
                          "Puede guardar archivos con un máximo de tamaño de 2 MB.");
    return;
  }
  QFile file(fileName);
  if(!file.open(QFile::ReadOnly)){
    QMessageBox::critical(this,qApp->applicationName(),
                          "Error al abrir el archivo.\n"+file.errorString());
    return;
  }
  ui->lineEdit_3->setText(fileName);
  imagen_2=file.readAll();
  file.close();
  file.flush();
}


void EditDataDialog::on_toolButton_3_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,"Cargar una imagen.",QDir::currentPath(),
                                                  "Imagenes (*.jpg *.jpeg *.png *.bmp)");
  if(fileName.isEmpty()){
    //    imagen_1=QByteArray();
    return;
  }
  QFileInfo info(fileName);
  if((info.size()/1024)>2048){
    QMessageBox::critical(this,qApp->applicationName(),
                          "El archivo que está intentando guardar es muy grande.\n"
                          "Puede guardar archivos con un máximo de tamaño de 2 MB.");
    return;
  }
  QFile file(fileName);
  if(!file.open(QFile::ReadOnly)){
    QMessageBox::critical(this,qApp->applicationName(),
                          "Error al abrir el archivo.\n"+file.errorString());
    return;
  }
  ui->lineEdit_4->setText(fileName);
  imagen_3=file.readAll();
  file.close();
  file.flush();
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
    if(mBox.exec()==QMessageBox::AcceptRole){
      //      qDebug()<<"Aceptaste tu muerte";
      //      return;
      imagen_2.clear();
      ui->lineEdit_3->clear();
    }else{
      //      qDebug()<<"Te salvaste";
      return;
    }
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
    if(mBox.exec()==QMessageBox::AcceptRole){
      //      qDebug()<<"Aceptaste tu muerte";
      //      return;
      imagen_3.clear();
      ui->lineEdit_4->clear();
    }else{
      //      qDebug()<<"Te salvaste";
      return;
    }

  });

}

void EditDataDialog::on_lineEdit_textChanged(const QString &arg1)
{
  ui->lineEdit->setText(arg1.toUpper());

}

