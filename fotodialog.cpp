#include "fotodialog.h"
#include "ui_fotodialog.h"
#include <QDebug>

FotoDialog::FotoDialog(QImage foto, QWidget *parent) :
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
//  QPixmap pixMap;
//pixMap.loadFromData(QPixmap::fromImage(_foto));
ui->lblFoto->setPixmap(QPixmap::fromImage(_foto).scaled(this->size(),Qt::KeepAspectRatio));
  this->resize(ui->lblFoto->size());
}
