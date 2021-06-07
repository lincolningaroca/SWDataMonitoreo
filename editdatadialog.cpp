#include "editdatadialog.h"
#include "ui_editdatadialog.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

EditDataDialog::EditDataDialog(QWidget *parent) :
  QDialog(parent), ui(new Ui::EditDataDialog)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
  loadGpoMinerolist();
//  setUpTableView();
}

EditDataDialog::~EditDataDialog()
{
  delete ui;
}

void EditDataDialog::loadGpoMinerolist()
{
  dataList=bLayer.gpoMineroList(BussinesLayer::GPO_MINERO);
  if(dataList.isEmpty()){
    QMessageBox::critical(this,qApp->applicationName(),"Error al cargar los datos\n"+
                                                           bLayer.errorMessage());
    return;
  }

  ui->cboGrupo->addItems(dataList.values());
  loadDataListCliente();
}

void EditDataDialog::loadDataListCliente()
{
  dataListCliente=bLayer.gpoMineroList(BussinesLayer::CLIENTE,
                                         dataList.key(ui->cboGrupo->currentText()));
  if(dataListCliente.isEmpty()){
    QMessageBox::critical(this,qApp->applicationName(),"Error al cargar los datos\n"+
                                                           bLayer.errorMessage());
    return;
  }
  ui->cboUnidad->addItems(dataListCliente.values());
  on_cboUnidad_activated(ui->cboUnidad->currentIndex());
}

void EditDataDialog::on_txtPath1_returnPressed()
{
  qDebug()<<"presionaste el control";
}

void EditDataDialog::on_btnCancelar_clicked()
{
  reject();
}

void EditDataDialog::on_cboGrupo_activated(int index)
{
  Q_UNUSED(index)
  ui->cboUnidad->clear();
  loadDataListCliente();
}

void EditDataDialog::on_cboUnidad_activated(int index)
{
  Q_UNUSED(index);
  model=new QSqlQueryModel(this);
  int id=dataListCliente.key(ui->cboUnidad->currentText());
  //  QSqlQueryModel qry=bLayer.data(id);

  model=bLayer.data(id);
  setUpTableView();
  ui->twEstaciones->setModel(model);
//  qDebug()<<id;
  ui->twEstaciones->setColumnWidth(1,150);
  ui->twEstaciones->setColumnWidth(2,150);
  ui->twEstaciones->hideColumn(0);
  ui->twEstaciones->hideColumn(3);

}

void EditDataDialog::setUpTableView()
{
  model->setHeaderData(1,Qt::Horizontal,"CODIGO DE ESTACIÓN");
  model->setHeaderData(2,Qt::Horizontal,"FECHA DE MUESTRA");

}


