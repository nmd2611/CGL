#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <algorithm>
#include<bits/stdc++.h>

QImage image(300,300,QImage::Format_RGB888);

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
int sign(int a, int b)
{
    if (a > b)
    {
        return 1;
    }
    else if (a == b)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
void bresenham(int x1, int x2, int y1,int y2)
{
    QRgb value;
    value = qRgb(0,255,0);
    int x = x1;
    int y = y1;
    int delta_x = abs(x2 - x1);
    int delta_y = abs(y2 - y1);
    int s1 = sign(x2,x1);
    int s2 = sign(y2,y1);
    int interchange = 0;
     if (delta_y > delta_x)
     {
         int tmp = delta_x;
         delta_x = delta_y;
         delta_y = tmp;
         interchange = 1;
     }

     int e_bar = (2 * delta_y) - delta_x;
     for (int i = 1; i <= delta_x; i++)
     {
        image.setPixel(x,y,value);
        while(e_bar > 0)
        {
            if (interchange == 1)
            {
                x = x + s1;
            }
            else
            {
                y = y + s2;
            }
            e_bar = e_bar - (2 * delta_x);
        }
        if(interchange == 1)
        {
            y = y + s2;
        }
        else
        {
            x = x + s1;
        }
        e_bar = e_bar + (2 * delta_y);
     }

}
void mh(int& xi, int& yi, int& delta_i)
{
    xi++;
    delta_i = delta_i + 2 * xi + 1;
}
void md(int& xi, int& yi, int& delta_i)
{
    xi++;
    yi--;
    delta_i = delta_i + 2 * xi - 2 * yi + 2;
}
void mv(int& xi, int& yi, int& delta_i)
{
    yi--;
    delta_i = delta_i - 2 * yi + 1;
}
void drawcircle(int x,int y,int radius)
{
    QRgb value;
    value = qRgb(0,255,0);
    int xi = 0;
    int yi = radius;
    int delta_i = 2 * ( 1 - radius);
    int limit = 0;
    int s = 0;
    while(yi >= limit)
    {
        image.setPixel(xi+x,yi+y,value);
        image.setPixel(x-xi,y-yi,value);
        image.setPixel(x+xi,y-yi,value);
        image.setPixel(x-xi,yi+y,value);
        if(delta_i < 0)
        {
            s = 2 * delta_i + 2 * yi -1;
            if(s <= 0)
                mh(xi,yi,delta_i);
            else
                md(xi,yi,delta_i);
        }
        else if(delta_i > 0)
        {
            s = 2 * delta_i - 2 * xi - 1;
            if(s <= 0)
                md(xi,yi,delta_i);
            else
                mv(xi,yi,delta_i);
        }
        else
            md(xi,yi,delta_i);
    }
}
void dda_circle(int xc,int yc,int r)
{

    QRgb value;
    value = qRgb(0,255,0);
   float xc1,xc2,yc1,yc2,eps,sx,sy;

  int val,i;

  xc1=r;

  yc1=0;

  sx=xc1;

  sy=yc1;

  i=0;

  do{

      val=pow(2,i);

      i++;

      }while(val<r);

  eps = 1/pow(2,i-1);

  do{

      xc2 = xc1 + yc1*eps;
      yc2 = yc1 - eps*xc2;

      image.setPixel(xc+xc2,yc-yc2,value);

      xc1=xc2;

      yc1=yc2;

     }while((yc1-sy)<eps || (sx-xc1)>eps);

}
void MainWindow::on_pushButton_clicked()
{
    float cos =  0.86602540378;
    int x = ui->textEdit->toPlainText().toInt();
    int y= ui->textEdit_2->toPlainText().toInt();
    float radius= ui->textEdit_3->toPlainText().toFloat();
    float pt_x = 0;
    float pt_y = 0;
    pt_x = (2*x-radius*cos)/2;
    pt_y = (2 * y + radius * 0.5 -radius)/2;
    int inner_rad = sqrt((x-pt_x)*(x-pt_x)+(y-pt_y)*(y-pt_y));
    //drawcircle(x,y,inner_rad);
    dda_circle(x,y,inner_rad);
    bresenham(x,(x+(radius*cos)),(y-radius),(y+(radius * 0.5)));
    bresenham(x,(x-radius*cos),(y-radius),(y+radius * 0.5));
    bresenham((x-radius*cos),(x+radius*cos),(y + radius * 0.5),(y+radius * 0.5));
    drawcircle(x,y,radius);
    //bresenham(0,299,0,299);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
