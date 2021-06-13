#ifndef SWCUSTOMTXT_H
#define SWCUSTOMTXT_H

#include <QLineEdit>
#include <QMouseEvent>
#include <QWidget>

class SWCustomTxt : public QLineEdit
{
  Q_OBJECT
public:
  SWCustomTxt(QWidget *parent=nullptr);
signals:
  void clicked();

  // QPaintDevice interface
public:
  virtual QPaintEngine *paintEngine() const override;

  // QWidget interface
protected:
  virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // SWCUSTOMTXT_H
