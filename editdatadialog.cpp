#include "editdatadialog.h"
#include "ui_editdatadialog.h"
#include <QDebug>

EditDataDialog::EditDataDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::EditDataDialog)
{
  ui->setupUi(this);
}

EditDataDialog::~EditDataDialog()
{
  delete ui;
}

void EditDataDialog::on_txtPath1_returnPressed()
{
  qDebug()<<"presionaste el control";
}

