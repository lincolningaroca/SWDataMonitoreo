#include "desc_pdialog.h"
#include "ui_Desc_pdialog.h"
#include <QPushButton>

Desc_pDialog::Desc_pDialog(int mode, QString descr, QWidget *parent) :
  QDialog(parent), ui(new Ui::Desc_pDialog)
{
  ui->setupUi(this);
  mo=mode;
  d=descr;
//  ui->txtDescPunto->setPlainText(d);
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
  if(mode==1){
    ui->txtDescPunto->setPlainText(d);
    ui->txtDescPunto->setReadOnly(true);

  }else{
    ui->txtDescPunto->setPlainText(d);
    //    ui->txtDescPunto->clear();
    ui->txtDescPunto->setReadOnly(false);
    btnGuardar=new QPushButton("Aceptar",this);
    btnGuardar->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_S));
    btnCancelar=new QPushButton("Cancelar",this);
    QHBoxLayout *hLayOut=new QHBoxLayout(nullptr);

    hLayOut->addStretch();
    hLayOut->addWidget(btnGuardar);
    hLayOut->addWidget(btnCancelar);
    qobject_cast<QVBoxLayout *>(this->layout())->addLayout(hLayOut);
    //    this->layout()->addItem(hLayOut);

    QObject::connect(btnGuardar,&QPushButton::clicked,[this](){
      _desc=ui->txtDescPunto->toPlainText();
//      d=ui->txtDescPunto->toPlainText();

      accept();
    });
    QObject::connect(btnCancelar,&QPushButton::clicked,this,&Desc_pDialog::reject);
  }
}

Desc_pDialog::Desc_pDialog(QString descr, QWidget *parent):
  QDialog(parent)
{
  d=descr;
  ui->txtDescPunto->setPlainText(d);

}

Desc_pDialog::~Desc_pDialog()
{
  delete ui;
}
