#include "fotodialog.h"
#include "ui_fotodialog.h"
#include <QDebug>

FotoDialog::FotoDialog(QByteArray foto, QWidget *parent) :
  QDialog(parent),ui(new Ui::FotoDialog)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);

  _foto=foto;
  loadFoto();

}

FotoDialog::~FotoDialog()
{
  delete ui;
}

void FotoDialog::loadFoto()
{
  QPixmap pixMap;
//  if(){
//    pixMap.load(":/img/logoEmpresa.png");
//    ui->lblFoto->setPixmap(pixMap.scaled(this->size(),Qt::KeepAspectRatio));
//    this->resize(ui->lblFoto->size());
//    return;
//  }

  pixMap.loadFromData(_foto);
  //  pixMap.scaled(634,434);
  //  ui->lblFoto->setScaledContents(true);

  ui->lblFoto->setPixmap(pixMap.scaled(this->size(),Qt::KeepAspectRatio));
  this->resize(ui->lblFoto->size());
//  ui->lblFoto->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}
