#ifndef EDITDATADIALOG_H
#define EDITDATADIALOG_H

#include <QDialog>

namespace Ui {
class EditDataDialog;
}

class EditDataDialog : public QDialog
{
  Q_OBJECT

public:
  explicit EditDataDialog(QWidget *parent = nullptr);
  ~EditDataDialog();

private slots:
  void on_txtPath1_returnPressed();

private:
  Ui::EditDataDialog *ui;
};

#endif // EDITDATADIALOG_H
