#ifndef NUEVAESTMONITOREODIALOG_H
#define NUEVAESTMONITOREODIALOG_H

#include <QDialog>
#include "bussineslayer.h"
#include <QFile>
#include <QAction>

namespace Ui {
class NuevaEstMonitoreoDialog;
}

class NuevaEstMonitoreoDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NuevaEstMonitoreoDialog(QWidget *parent = nullptr);
  ~NuevaEstMonitoreoDialog();
  void loadGpoMinerolist();
  void loadDataListCliente();
  void setUpToolBtnClear();

private slots:
  void on_btnGuardar_clicked();
  void on_cboGrupo_activated(int index);
  void on_btnFoto1_clicked();
  void on_btnCancelar_clicked();
  void on_btnFoto2_clicked();
  void on_btnFoto3_clicked();
  void on_txtPath1_textChanged(const QString &arg1);
  void on_txtPath2_textChanged(const QString &arg1);

  void on_pushButton_clicked();

private:
  Ui::NuevaEstMonitoreoDialog *ui;
  BussinesLayer bLayer;
  QFile file;
  QHash<int,QString> dataList;
  QHash<int,QString> dataListCliente;

  QByteArray imagen_1;
  QByteArray imagen_2;
  QByteArray imagen_3;

  QVariant _idEstacion;

  QString desc_punto;
};

#endif // NUEVAESTMONITOREODIALOG_H
