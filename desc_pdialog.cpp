#include "desc_pdialog.h"
#include "ui_desc_pdialog.h"

Desc_pDialog::Desc_pDialog(QString desc, QWidget *parent) :
  QDialog(parent), ui(new Ui::Desc_pDialog)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
  ui->txtDescPunto->setPlainText(desc);
}

Desc_pDialog::~Desc_pDialog()
{
  delete ui;
}
