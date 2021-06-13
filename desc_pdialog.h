#ifndef DESC_PDIALOG_H
#define DESC_PDIALOG_H

#include <QDialog>

namespace Ui {
class Desc_pDialog;
}

class Desc_pDialog : public QDialog
{
  Q_OBJECT

public:
  explicit Desc_pDialog(int mode,QString desc=QString(), QWidget *parent = nullptr);
//  Desc_pDialog(QWidget *parent = nullptr);
  ~Desc_pDialog();

  QString desc(){return _desc;}

private:
  Ui::Desc_pDialog *ui;
  QPushButton *btnGuardar;
  QPushButton *btnCancelar;
  QString _desc;
};

#endif // DESC_PDIALOG_H
