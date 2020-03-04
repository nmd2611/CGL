#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>

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

void MainWindow::displayBresenhmCircle(int xc_,int yc_, int x, int y)
{
    QImage image;
            image.setPixel(150+xc_+x,150+yc_+y,qRgb(0,255,0));
            image.setPixel(150-(xc_-x),150+yc_+y,qRgb(0,255,0));
            image.setPixel(150 +xc_+x,150-(yc_-y),qRgb(0,255,0));
            image.setPixel(150-(xc_-x),150-(yc_-y),qRgb(0,255,0));

           //displaying all 8 coordinates of(x,y) residing in 8-octants
          /* putpixel(xc_+x, yc_+y, WHITE);
           putpixel(xc_-x, yc_+y, WHITE);
           putpixel(xc_+x, yc_-y, WHITE);
           putpixel(xc_-x, yc_-y, WHITE);
           putpixel(xc_+y, yc_+x, WHITE);
           putpixel(xc_-y, yc_+x, WHITE);
           putpixel(xc_+y, yc_-x, WHITE);
           putpixel(xc_-y, yc_-x, WHITE);*/
 }




void MainWindow::breshnam(int xc_,int yc_,int radius_)
{

     int d,d1;
    int x = 0, y = radius_;
     int D = 2*(1-radius_);
//          displayBresenhmCircle(xc_, yc_, x, y);
          int limit = 0;
       while (y >= limit)
       {

          paint.drawPoint(xc_+x,yc_+y);
           if(D<0)
           {
               int d = 2*D + 2*y -1;
               if(d<=0)
               {
                   x = x+1;
                   D = D+ 2*x + 1;
               }
               else
               {
                   x = x+1;
                   y = y-1;
                   D = D+2*x -2*y +2;
               }
           }
           else if(D>0)
           {
               d1 = 2*d-2*x-1;
               if(d1>0)
               {
                   y = y-1;
                   D =D+ 2*y+1;
               }
               else
               {
                   x = x+1;
                   y = y-1;
                   D = D+2*x -2*y +2;
               }
           }
           else
           {
               x = x+1;
               y = y-1;
               D = D+2*x-2*y+2;
           }
           /*paint.drawPoint(xc_+x,yc_-y);
                paint.drawPoint(xc_-x,yc_-y);
                paint.drawPoint(xc_+x,yc_+y);
               paint.drawPoint(xc_-x,yc_+y);
                paint.drawPoint(xc_+y,yc_-x);
                paint.drawPoint(xc_-y,yc_-x);
               paint.drawPoint(xc_+y,yc_+x);
                paint.drawPoint(xc_-y,yc_+x);*/
        }
}

void MainWindow::on_pushButton_clicked()
{

    paint.begin(&pic);
    int r = ui->textEdit->toPlainText().toInt();
    int x1 = ui->textEdit_2->toPlainText().toInt();
    int y1 = ui->textEdit_3->toPlainText().toInt();
    breshnam(x1,y1,r);
     paint.end();
    ui->label_4->setPicture(pic);
}
