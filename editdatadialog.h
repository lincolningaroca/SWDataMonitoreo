#ifndef EDITDATADIALOG_H
#define EDITDATADIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QAction>

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
  QString desc_punto;

  QString newPath_1;
  QString newPath_2;
  QString newPath_3;

  QImage imagen_1;
  QImage imagen_2;
  QImage imagen_3;

  void dataModel();
//  void cleanData();
  void manageControls(int op);
  QImage openPicture(QString f);
//  QImage removePicture(QString f);
  //funcoines privadas del programador
  void setUpTableView();

  void setUpToolBtnClear();
  void setupFotoDialog();

  // QPaintDevice interface
public:
  virtual QPaintEngine *paintEngine() const override;

  // QWidget interface
protected:
  virtual void closeEvent(QCloseEvent *event) override;
};

#endif // EDITDATADIALOG_H
