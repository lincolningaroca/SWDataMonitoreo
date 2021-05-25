#include "nuevodialog.h"
#include "ui_nuevodialog.h"
#include <QMessageBox>

NuevoDialog::NuevoDialog(DialogMode mode, QWidget *parent) :
  QDialog(parent),_mode(mode), ui(new Ui::NuevoDialog)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  if(mode==GRUPO)
  {
    ui->lblNombre->setText("Nombre consorcio o grupo minero: ");
    ui->lblGrupo->setVisible(false);
    ui->cboLista->setVisible(false);
  }else{
    ui->lblNombre->setText("Nombre unidad minera: ");
    ui->lblGrupo->setVisible(true);
    ui->cboLista->setVisible(true);
    loadDataList();
  }

  //  regex.setPattern("^\\S[\\w\\w]+$");
  regex.setPattern("^([a-zA-ZñÑ.-]\\s?)+\\S$");
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
  QStringList param;
  param<<ui->txtNombre->text().toUpper()<<ui->teDescripcion->toPlainText();
  if(!regex.match(ui->txtNombre->text()).hasMatch()){
    QMessageBox::warning(this,qApp->applicationName(),
                         "El campo nombre no puede contener espacios en blanco al principio o al final.\n"
                         "Asi mismo, Verifique que el campo no este vacío.");
    ui->txtNombre->selectAll();
    ui->txtNombre->setFocus();
    return;
  }
  if(_mode==GRUPO){
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
  }else{
    QVariantList param;
    param.append(ui->txtNombre->text());
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
  }

  QMessageBox::warning(this,qApp->applicationName(),"Datos guardados.");
  accept();


}

void NuevoDialog::on_btnCancelar_clicked()
{
  reject();
}

