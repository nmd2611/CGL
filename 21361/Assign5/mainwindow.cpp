#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<grp.h>
#include<qpainter.h>
#include<qpicture.h>
#include<math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
QImage img(600,600,QImage::Format_RGB888);
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
;
}


void MainWindow::Flood_fill(int x,int y,int fillcolor,int bkcolor)
{
     ui->label_4->setText(QString("ajshaj"));
    if(img.pixel(x,y) == bkcolor)
    {
        ui->label_4->setText(QString("ajshaj"));
        img.setPixel(x,y,fillcolor);
        Flood_fill(x+1,y,fillcolor,bkcolor);
        Flood_fill(x,y+1,fillcolor,bkcolor);
        Flood_fill(x-1,y,fillcolor,bkcolor);
        Flood_fill(x,y-1,fillcolor,bkcolor);
    }
}





void MainWindow::on_pushButton_clicked()
{
     paint.begin(&pic);

    int x = ui->textEdit->toPlainText().toInt();
     int y = ui->textEdit_2->toPlainText().toInt();
      int len = ui->textEdit_3->toPlainText().toInt();
    /*  bresenham(x,y,x+len,y);
      bresenham(x+len,y,x+len,y+len);
      bresenham(x+len,y+len,x,y+len); +len*i
      bresenham(x,y+len,x,y);*/
//      for(int i=0;i<4;i++)
//      {

//              bresenham(x+len*i,y,x+len+len*i,y);
//              bresenham(x+len+len*i,y,x+len+len*i,y+len);
//              bresenham(x+len+len*i,y+len,x+len*i,y+len);
//              bresenham(x+len*i,y+len,x+len*i,y);
//      }
     ui->label_4->setText(QString("Enter tx&ty or sx&sy"));
        int x1 = x;
        int y1 = y;
      for(int i=0;i<4;i++)
      {
              for(int i=0;i<4;i++)
              {
                        double angle;
                        angle=45*3.142/180;
                      bresenham(x1+len*i ,y1,x1+len+len*i,y1);
                      bresenham(x1+len+len*i,y1,x1+len+len*i,y1+len);
                      bresenham(x1+len+len*i,y1+len,x1+len*i,y1+len);
                      bresenham(x1+len*i,y1+len,x1+len*i,y1);
              }
              y1 = y1+len;
      }
        Flood_fill(x,y,250,0);

      paint.end();
      ui->label_4->setPicture(pic);
}
