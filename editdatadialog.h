#ifndef EDITDATADIALOG_H
#define EDITDATADIALOG_H

#include <QDialog>
#include "bussineslayer.h"

namespace Ui {
class EditDataDialog;
}

class EditDataDialog : public QDialog
{
  Q_OBJECT

public:
  explicit EditDataDialog(QWidget *parent = nullptr);
  ~EditDataDialog();

  //funciones del programador
  void loadGpoMinerolist();
  void loadDataListCliente();

private slots:
  void on_txtPath1_returnPressed();
  void on_btnCancelar_clicked();
  void on_cboGrupo_activated(int index);
  void on_cboUnidad_activated(int index);

private:
  Ui::EditDataDialog *ui;
  BussinesLayer bLayer;
  QHash<int,QString> dataList;
  QHash<int,QString> dataListCliente;
  QSqlQueryModel *model;

  //funcoines privadas del programador
  void setUpTableView();
};

#endif // EDITDATADIALOG_H
