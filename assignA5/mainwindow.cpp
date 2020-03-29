#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include "QMouseEvent"
#include "QColorDialog"
#include <cmath>
#include<bits/stdc++.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


QImage image(700,700,QImage::Format_RGB888);
QRgb value = qRgb(0,255,0);


MainWindow::~MainWindow()
{
    delete ui;
}

int sign(int a)
{
    if (a > 0)
    {
        return 1;
    }
    else if (a <0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void MainWindow:: BresenhamLine(int x1,int y1, int x2, int y2)
{
    int x,y;
    x=x1;
    y=y1;
    int dx= abs(x2-x1);
    int dy = abs(y2-y1);

    int s1= sign(x2-x1);
    int s2= sign(y2-y1);
    int inter;
     int temp;
     if(dy>dx)
     {
         temp=dx;
         dx=dy;
         dy=temp;
         inter=1;
     }
     else
         inter =0;

     int e= 2*y - dx;
     for(int i=0;i<dx;i++)
     {
        image.setPixel(x,y,value);
        while(e>0)
        {
            if(inter == 1)
                x+=s1;
            else
                y+=s2;
            e=e- 2*dx;
        }
        if(inter == 1)
            y+=s2;
        else
            x+=s1;
        e=e+ 2*dy;
     }

     ui->label->setPixmap(QPixmap::fromImage(image));
     ui->label->show();
}

void MainWindow::drawPolygon()
{
    int x1,y1,x2,y2;
    x1=150;
    y1=550;
    x2=550;
    y2=150;

    // draw outer frame
    BresenhamLine(x1,y1,x2,y1);
    BresenhamLine(x1,y1,x1,y2);
    BresenhamLine(x2,y1,x2,y2);
    BresenhamLine(x1,y2,x2,y2);

}

void MainWindow::on_pushButton_clicked()
{
    // draw
    image.setPixel(150,550,value);
    image.setPixel(550,150,value);
    //BresenhamLine(150,550,550,550);
    //BresenhamLine(150,550,150,150);
    //BresenhamLine(550,550,550,150);
    drawPolygon();
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    // rotate
}

void MainWindow::on_pushButton_3_clicked()
{
    // fill colour
}
