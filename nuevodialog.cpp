#include "nuevodialog.h"
#include "ui_nuevodialog.h"
#include <QMessageBox>

NuevoDialog::NuevoDialog(DialogMode mode, QVariantList data, QWidget *parent) :
  QDialog(parent), ui(new Ui::NuevoDialog)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
  _mode=mode;
  _data=data;

  setUpForm();

  loadDataListCliente();
}

NuevoDialog::~NuevoDialog()
{
  delete ui;
}

void NuevoDialog::loadDataList()
{
  dataList=bussines.gpoMineroList(BussinesLayer::GPO_MINERO);
  ui->cboLista->addItems(dataList.values());
}

void NuevoDialog::on_btnGuardar_clicked()
{

  if(ui->txtNombre->text().simplified().isEmpty()){

    QMessageBox::warning(this,qApp->applicationName(),
                         "El campo nombre no puede contener espacios en blanco al principio o al final.\n"
                         "Asi mismo, Verifique que el campo no este vacío.");
    ui->txtNombre->selectAll();
    ui->txtNombre->setFocus();
    return;
  }
  if(_mode==GRUPO){
    QVariantList param;
    param<<ui->txtNombre->text().toUpper()<<ui->teDescripcion->toPlainText();
    if(!bussines.gpoMineroAction(param,BussinesLayer::INSERT)){
      if(bussines.errorCode()=="23505"){
        QMessageBox::warning(this,qApp->applicationName(),
                             "Este nombre ya esta registrado en la base de datos.\n"
                             "Por favor intente con uno nuevo.");
        ui->txtNombre->selectAll();
        ui->txtNombre->setFocus(Qt::OtherFocusReason);
        return;
      }
    }
    //      QMessageBox::information(this,qApp->applicationName(),"Datos guardados.");
    //      accept();
  }else if(_mode==UNIDAD){
    QVariantList param;
    param.append(ui->txtNombre->text().toUpper());
    param.append(ui->teDescripcion->toPlainText());
    param.append(dataList.key(ui->cboLista->currentText()));

    if(!bussines.clienteMineroAction(param,BussinesLayer::INSERT)){
      if(bussines.errorCode()=="23505"){
        QMessageBox::warning(this,qApp->applicationName(),
                             "Este nombre ya esta registrado en la base de datos.\n"
                             "Por favor intente con uno nuevo.");
        ui->txtNombre->selectAll();
        ui->txtNombre->setFocus(Qt::OtherFocusReason);
        return;
      }
    }
    //      QMessageBox::information(this,qApp->applicationName(),"Datos guardados.");
    //      accept();
  }else if(_mode==UPDATE_GPO){
    QVariantList paramg;
    paramg.append(ui->txtNombre->text().toUpper());
    paramg.append(ui->teDescripcion->toPlainText());
    paramg.append(_data.value(0));
    if(!bussines.gpoMineroAction(paramg,BussinesLayer::UPDATE)){
      if(bussines.errorCode()=="23505"){
        QMessageBox::warning(this,qApp->applicationName(),
                             "Este nombre ya esta registrado en la base de datos.\n"
                             "Por favor intente con uno nuevo.");
        ui->txtNombre->selectAll();
        ui->txtNombre->setFocus(Qt::OtherFocusReason);
        return;
      }
    }
    //      QMessageBox::information(this,qApp->applicationName(),"Datos actualizados.");
    //      accept();
  }else{
    QVariantList param;
    param.append(ui->txtNombre->text().toUpper());
    param.append(ui->teDescripcion->toPlainText());
    param.append(dataList.key(ui->cboLista->currentText()));
    param.append(dataListCliente.key(ui->lwUnidades->currentItem()->data(
                                                                    Qt::DisplayRole).toString()));
    if(!bussines.clienteMineroAction(param,BussinesLayer::UPDATE)){
      if(bussines.errorCode()=="23505"){
        QMessageBox::warning(this,qApp->applicationName(),
                             "Este nombre ya esta registrado en la base de datos.\n"
                             "Por favor intente con uno nuevo.");
        ui->txtNombre->selectAll();
        ui->txtNombre->setFocus(Qt::OtherFocusReason);
        return;
      }
    }

  }


  QMessageBox::information(this,qApp->applicationName(),"Datos guardados.");
  accept();


}

void NuevoDialog::on_btnCancelar_clicked()
{
  reject();
}
void NuevoDialog::loadDataListCliente()
{
  dataListCliente=bussines.gpoMineroList(BussinesLayer::CLIENTE,
                                           dataList.key(ui->cboLista->currentText()));
  //dataListCliente=bussines.gpoMineroList(BussinesLayer::CLIENTE,38);
  QStringList values=dataListCliente.values();
  for(int i=0;i<values.count();++i){
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/img/ui-11-128.png"),
                                                values.value(i));
    ui->lwUnidades->addItem(item);
  }

  if(_mode==UPDATE_UNIDAD){
    ui->lwUnidades->setCurrentRow(0);
    on_lwUnidades_itemClicked(ui-> lwUnidades->currentItem());
//    QObject::connect(ui->lwUnidades->selectionModel(),&QItemSelectionModel::currentChanged,this,
//                     [&](){
//                       on_lwUnidades_itemClicked(ui->lwUnidades->currentItem());
//                     });
  }

}

void NuevoDialog::on_cboLista_activated(int index)
{
  Q_UNUSED(index)
  ui->lwUnidades->clear();
  loadDataListCliente();
  //  qDebug()<<dataList.key(ui->cboLista->currentText());
  //  qDebug()<<dataListCliente.value(1);

}

void NuevoDialog::setUpForm()
{
  switch (_mode) {
    case GRUPO:
      ui->lblNombre->setText("Nombre consorcio o grupo minero: ");
      ui->lblGrupo->setVisible(false);
      ui->cboLista->setVisible(false);
      ui->lwUnidades->setVisible(false);
      break;
    case UPDATE_GPO:
      ui->lblNombre->setText("Nombre consorcio o grupo minero: ");
      ui->lblGrupo->setVisible(false);
      ui->cboLista->setVisible(false);
      ui->lwUnidades->setVisible(false);
      ui->txtNombre->setText(_data.value(1).toString());
      ui->teDescripcion->setPlainText(_data.value(2).toString());
      break;

    case UNIDAD:
      ui->lblNombre->setText("Nombre unidad minera: ");
      ui->lblGrupo->setVisible(true);
      ui->cboLista->setVisible(true);
      ui->lwUnidades->setVisible(false);
      loadDataList();
      break;
    case UPDATE_UNIDAD:
      ui->lblNombre->setText("Nombre unidad minera: ");
      ui->lblGrupo->setVisible(true);
      ui->cboLista->setVisible(true);
      loadDataList();
      break;

    default:
      break;

  }

}

void NuevoDialog::on_lwUnidades_itemClicked(QListWidgetItem *item)
{
  QVariantList dataCte=bussines.selectData(
    dataListCliente.key(item->data(Qt::DisplayRole).toString()),BussinesLayer::CLIENTE);
  ui->txtNombre->setText(dataCte.value(1).toString());
  ui->teDescripcion->setPlainText(dataCte.value(2).toString());
}

