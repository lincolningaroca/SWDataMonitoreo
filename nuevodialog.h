#ifndef NUEVODIALOG_H
#define NUEVODIALOG_H

#include "bussineslayer.h"
#include <QDialog>
#include <QRegularExpression>

namespace Ui {
class NuevoDialog;
}

class NuevoDialog : public QDialog
{
  Q_OBJECT

public:
  enum DialogMode{
    GRUPO,
    UNIDAD
  };

  explicit NuevoDialog(DialogMode mode, QWidget *parent = nullptr);
  ~NuevoDialog();

  void loadDataList();


private slots:
  void on_btnGuardar_clicked();
  void on_btnCancelar_clicked();

private:
  Ui::NuevoDialog *ui;
  BussinesLayer bussines;
  QRegularExpression regex;
  QHash<int,QString> dataList;

  DialogMode _mode;

};

#endif // NUEVODIALOG_H
