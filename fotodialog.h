#ifndef FOTODIALOG_H
#define FOTODIALOG_H

#include <QDialog>

namespace Ui {
class FotoDialog;
}

class FotoDialog : public QDialog
{
  Q_OBJECT

public:
  explicit FotoDialog(QImage foto,QWidget *parent = nullptr);

  ~FotoDialog();

private:
  Ui::FotoDialog *ui;
  QImage _foto;
  void loadFoto();
};

#endif // FOTODIALOG_H
