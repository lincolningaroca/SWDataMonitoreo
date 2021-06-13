#include "swcustomtxt.h"

SWCustomTxt::SWCustomTxt(QWidget *parent):QLineEdit(parent)
{

}

QPaintEngine *SWCustomTxt::paintEngine() const
{
  return QWidget::paintEngine();

}

void SWCustomTxt::mousePressEvent(QMouseEvent *event)
{
  if(event->button()==Qt::LeftButton){
    emit clicked();
  }
  QLineEdit::mousePressEvent(event);
}
