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
  explicit Desc_pDialog(QString desc, QWidget *parent = nullptr);
  ~Desc_pDialog();

private:
  Ui::Desc_pDialog *ui;
};

#endif // DESC_PDIALOG_H
