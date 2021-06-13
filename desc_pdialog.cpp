#include "desc_pdialog.h"
#include "ui_desc_pdialog.h"
#include <QPushButton>

Desc_pDialog::Desc_pDialog(int mode, QString descr, QWidget *parent) :
  mo(mode),d(descr),QDialog(parent), ui(new Ui::Desc_pDialog)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
  if(mode==1){
    ui->txtDescPunto->setPlainText(d);
    ui->txtDescPunto->setReadOnly(true);

  }else{
    ui->txtDescPunto->setPlainText(d);
//    ui->txtDescPunto->clear();
    ui->txtDescPunto->setReadOnly(false);
    btnGuardar=new QPushButton("Aceptar",this);
    btnCancelar=new QPushButton("Cancelar",this);
    QHBoxLayout *hLayOut=new QHBoxLayout(this);

    hLayOut->addStretch();
    hLayOut->addWidget(btnGuardar);
    hLayOut->addWidget(btnCancelar);
    this->layout()->addItem(hLayOut);
    QObject::connect(btnGuardar,&QPushButton::clicked,this,[&](){
      _desc=ui->txtDescPunto->toPlainText();
      accept();
    });
    QObject::connect(btnCancelar,&QPushButton::clicked,this,&Desc_pDialog::reject);
  }



}

Desc_pDialog::Desc_pDialog(QString descr, QWidget *parent):
  d(descr),QDialog(parent)
{


}


Desc_pDialog::~Desc_pDialog()
{
  delete ui;
}
