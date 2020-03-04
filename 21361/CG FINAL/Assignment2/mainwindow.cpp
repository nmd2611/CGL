#include "mainwindow.h"
#include "ui_mainwindow.h"
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
void MainWindow::drawBCircle(int x1, int y1, int r)
{
    int x,y;
    int d,d1,d2;


    //Drawinfg centre
  //Drawing text and radius value in circle
//        paint.drawLine(QPoint(x1+200,200-y1),QPoint(x1+200+r,200-y1));
//        QString rad=QString::number(r);
//        rad="r="+rad;
//        paint.drawText(QPoint(x1+200+10,200-y1+10),rad);
//        QString xco=QString::number(x1);
//        QString yco=QString::number(y1);
//        xco="C("+xco+","+yco+")";
//        paint.drawText(QPoint(x1+200-12,200-y1-12),xco);
    x=0;
    y=r;
    d=2*(1-r);
    while(y!=0)
    {
      paint.drawPoint(x1+x+200,200-y1+y);
      paint.drawPoint(x1+x+200,200-y1+(-1*y));
      paint.drawPoint(x1+(-1*x)+200,200-y1+(-1*y));
      paint.drawPoint(x1+(-1*x)+200,200-y1+y);
        if(d<0)
        {
            d1=2*d+2*y-1;
            if(d1<=0)  //MH
            {
                x=x+1;
                d=d+2*x+1;
            }
            else //MD
            {
                x=x+1;
                y=y-1;
                d=d+2*x-2*y+2;
            }
        }
        else if(d>0)
        {
            d2=2*d-2*x-1;
            if(d2<0) //MD
            {
                x=x+1;
                y=y-1;
                d=d+2*x-2*y+2;
            }
            else //MV
            {
                y=y-1;
                d=d-2*y+1;
            }
        }
        else    //MD
        {
            x=x+1;
            y=y-1;
            d=d+2*x-2*y+2;
        }
    }
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
    paint.drawPoint(round(x)+200,200-round(y));
          //  img.setPixel(round(x)+150,150-round(y),qRgb(128,15,45));
            x=x+xinc;
            y=y+yinc;
            i++;
        }
}

void MainWindow::on_pushButton_clicked()
{
    int x1=ui->textEdit->toPlainText().toInt();
    int y1=ui->textEdit_2->toPlainText().toInt();
    int r=ui->textEdit_3->toPlainText().toInt();

    paint.begin(&pic);
    paint.drawLine(QPoint(200,0),QPoint(200,400));
    paint.drawLine(QPoint(0,200),QPoint(400,200));

    drawBCircle(x1,y1,r); //Outer Circle
    //      /\
    //     /  \
    //     ----
    bresenham(0+x1,r+y1,round(0.866025*r)+x1,-0.5*r+y1);  //left line
   bresenham(0+x1,r+y1,round(-0.866025*r)+x1,-0.5*r+y1);  //right line
    bresenham(round(-0.866025*r)+x1,-0.5*r+y1,round(0.866025*r)+x1,-0.5*r+y1); //horizontal line
      drawBCircle(x1,y1,r/2);
    paint.end();
    ui->label_4->setPicture(pic);
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
        paint.drawPoint(200+x,200-y);
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
