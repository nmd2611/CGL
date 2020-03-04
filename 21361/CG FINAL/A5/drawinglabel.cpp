#include "drawinglabel.h"

drawingLabel::drawingLabel(QWidget *parent) : QLabel(parent)
{
     startY=startX=X1=X2=Y1=Y2=0;
     count=0;
     polygonComplete=false;
}

void drawingLabel::mousePressEvent(QMouseEvent *ev)
{
   if(polygonComplete)
       return;
   if(count==0)
   {
       x=startX=X1=X2=ev->pos().x();
       y=startY=Y1=Y2=ev->pos().y();
       count++;
       emit(Mouse_RecordStart());
   }
   else
   {
       if(startX-2<=ev->pos().x() && ev->pos().x()<=startX+2 && startY-2<=ev->pos().y()
               && ev->pos().y()<=startY+2)
       {
           X1=X2;
           Y1=Y2;
           X2=startX;
           Y2=startY;
           polygonComplete=true;
       }
       else
       {
           count++;
           X1=X2;
           Y1=Y2;
           X2=ev->pos().x();
           Y2=ev->pos().y();
       }
       emit(Mouse_Click());
   }
}

void drawingLabel::mouseMoveEvent(QMouseEvent *ev)
{
   this->x=ev->pos().x();
   this->y=ev->pos().y();
    emit(Mouse_Hover());
}

void drawingLabel::mouseDoubleClickEvent(QMouseEvent *ev)
{
    this->x=ev->pos().x();
    this->y=ev->pos().y();
    emit(Mouse_DClick());
}
