#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qpainter.h>
#include<qpicture.h>
#include<math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int sign(float val)
{
    if(val<0)
    {
        return -1;
    }
    else if(val==0)
        return 0;
    else
        return 1;
}
void MainWindow::bresenham(int x1,int y1,int x2,int y2)
{

    int s1,s2,interchange,x,y,i;
    float dx,dy,e;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    x=x1;
    y=y1;
    s1=sign(x2-x1);
    s2=sign(y2-y1);

    if(dx<dy)
    {
        float temp=dx;
        dx=dy;
        dy=temp;
        interchange=1;
    }
    else
        interchange=0;
    i=1;
    e=2*dy-dx;
    while(i<=dx)
    {
        paint.drawPoint(150+x,150-y);
//            if(i==1)
//            {

//                QString sx=QString::number(x);
//                QString sy=QString::number(y);
//                sx="("+sx+" , "+sy+")";
//                paint.drawText(QPoint(150+x+10,150-y+10),sx);
//            }
        while(e>0)
        {
            if(interchange==1)
            {
                x=x+s1;
            }
            else
            {
                y=y+s2;
            }
            e=e-2*dx;
        }
        if(interchange==1)
        {
            y=y+s2;
        }
        else
        {
            x=x+s1;
        }
        e=e+2*dy;
        i++;
    }
//        QString sx=QString::number(x);
//        QString sy=QString::number(y);
//        sx="("+sx+" , "+sy+")";
//        paint.drawText(QPoint(150+x+10,150-y+10),sx);
}
void MainWindow::dda(int x1, int y1, int x2, int y2)
{
    int dx=(x2-x1);
        int dy=(y2-y1);
        int length;
        float x,y;
        if(abs(dx)>=abs(dy))
            length=abs(dx);
        else
            length=abs(dy);

        float xinc=dx/float(length);
        float yinc=dy/float(length);

        x=x1;
        y=y1;
        int i=1;
        while(i<=length)
        {
           // float ty=(y);
    paint.drawPoint(round(x)+150,150-round(y));
          //  img.setPixel(round(x)+150,150-round(y),qRgb(128,15,45));
            x=x+xinc;
            y=y+yinc;
            i++;
        }
}

void MainWindow::on_pushButton_clicked()
{    paint.begin(&pic);
    int x1=ui->textEdit->toPlainText().toInt();
        int y1=ui->textEdit_2->toPlainText().toInt();
        int x2=ui->textEdit_3->toPlainText().toInt();
        int y2=ui->textEdit_4->toPlainText().toInt();

        QBrush brush;
        brush.setColor(Qt::yellow);
        paint.setBrush(brush);
        paint.setPen(Qt::red);
        paint.drawLine(QPoint(150,0),QPoint(150,300));
        paint.drawLine(QPoint(0,150),QPoint(300,150));

        bresenham(x1,y1,x2,y1);
        bresenham(x2,y1,x2,y2);
        bresenham(x1,y1,x1,y2);
        bresenham(x1,y2,x2,y2);

        int xmid,ymid;
        xmid=(x1+x2)/2;
        ymid=(y1+y2)/2;

        dda(xmid,y1,x2,ymid);
         dda(x2,ymid,xmid,y2);
           dda(xmid,y2,x1,ymid);
             dda(x1,ymid,xmid,y1);

int xx1,yy1,xx2,yy2;
xx1=(xmid+x1)/2;
yy1=(ymid+y1)/2;
xx2=(xmid+x2)/2;
yy2=(ymid+y2)/2;

bresenham(xx1,yy1,xx2,yy1);
bresenham(xx2,yy1,xx2,yy2);
bresenham(xx1,yy1,xx1,yy2);
bresenham(xx1,yy2,xx2,yy2);
        paint.end();
        ui->label_5->setPicture(pic);
}
