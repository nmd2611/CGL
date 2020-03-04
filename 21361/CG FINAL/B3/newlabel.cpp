#include "newlabel.h"

newLabel::newLabel(QWidget *parent) : QLabel(parent)
{

}
void newLabel::mousePressEvent(QMouseEvent *ev)
{
    if(firstPoint)
    {
        x1=ev->pos().x();
        y1=ev->pos().y();
        firstPoint=false;
        emit(FirstPoint());
    }
    else
    {
        x2=ev->pos().x();
        y2=ev->pos().y();
        firstPoint=true;
        emit(SecondPoint());
    }
}
