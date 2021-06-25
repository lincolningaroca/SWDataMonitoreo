#ifndef DESC_PDIALOG_H
#define DESC_PDIALOG_H

#include <QDialog>
#include <QHBoxLayout>

namespace Ui {
class Desc_pDialog;
}

class Desc_pDialog : public QDialog
{
  Q_OBJECT

public:
  explicit Desc_pDialog(int mode,QString descr=QString(), QWidget *parent = nullptr);
  Desc_pDialog(QString descr=QString(), QWidget *parent = nullptr);
//  Desc_pDialog(QWidget *parent = nullptr);
  ~Desc_pDialog();

  QString desc(){return _desc;}
  void setDesc(QString d){this->d=d;}

private:
  Ui::Desc_pDialog *ui;
  QPushButton *btnGuardar;
  QPushButton *btnCancelar;
  QString _desc;
  QString d;
  int mo;

};

#endif // DESC_PDIALOG_H
