#ifndef EDITDATADIALOG_H
#define EDITDATADIALOG_H

#include <QDialog>
#include "bussineslayer.h"
#include "dbconection.h"
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QAction>


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
  void datosMonitoreo();

private slots:
//  void on_txtPath1_returnPressed();
  void on_btnCancelar_clicked();
  void on_cboGrupo_activated(int index);
  void on_cboUnidad_activated(int index);
  void on_btnEliminar_clicked();
  void on_btnGuardar_clicked();
  void on_toolButton_clicked();
  void on_pushButton_clicked();
  void on_toolButton_2_clicked();
  void on_toolButton_3_clicked();


private:
  Ui::EditDataDialog *ui;
  BussinesLayer bLayer;
  QHash<int,QString> dataList;
  QHash<int,QString> dataListCliente;
  QSqlQueryModel *model;
  QVariantList list;

  QByteArray imagen_1;
  QByteArray imagen_2;
  QByteArray imagen_3;

  void dataModel();
  void cleanData();
  void manageControls(int op);

  //funcoines privadas del programador
  void setUpTableView();
  DbConection db;
  QString desc_punto;
  void setUpToolBtnClear();

  // QPaintDevice interface
public:
  virtual QPaintEngine *paintEngine() const override;

  // QWidget interface
protected:
  virtual void closeEvent(QCloseEvent *event) override;
};

#endif // EDITDATADIALOG_H
