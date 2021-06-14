#ifndef NUEVODIALOG_H
#define NUEVODIALOG_H

#include "bussineslayer.h"
#include <QDialog>
//#include <QRegularExpression>
#include <QListWidgetItem>

namespace Ui {
class NuevoDialog;
}

class NuevoDialog : public QDialog
{
  Q_OBJECT

public:
  enum DialogMode{
    GRUPO,
    UNIDAD,
    UPDATE_GPO,
    UPDATE_UNIDAD
  };

  explicit NuevoDialog(DialogMode mode, QVariantList data=QVariantList(), QWidget *parent = nullptr);
  ~NuevoDialog();

  void loadDataList();
  void loadDataListCliente();

private slots:
  void on_btnGuardar_clicked();
  void on_btnCancelar_clicked();
  void on_cboLista_activated(int index);
  void on_lwUnidades_itemClicked(QListWidgetItem *item);

  void on_txtNombre_textChanged(const QString &arg1);

private:
  Ui::NuevoDialog *ui;
  BussinesLayer bussines;
//  QRegularExpression regex;
  QHash<int,QString> dataList;
  QHash<int,QString> dataListCliente;

  DialogMode _mode;
  QVariantList _data;
  void setUpForm();

};

#endif // NUEVODIALOG_H
