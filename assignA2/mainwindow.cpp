#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include<QLabel>
#include<algorithm>

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

    QImage image(500,500,QImage::Format_RGB888);
    QRgb value=qRgb(0,255,0);    //set the colour value


void MainWindow::printCircle(int xc, int yc, int x, int y)
    {
            image.setPixel(xc+x, yc+y, value);
            image.setPixel(xc-x, yc+y, value);
            image.setPixel(xc+x, yc-y, value);
            image.setPixel(xc-x, yc-y, value);
            image.setPixel(xc+y, yc+x, value);
            image.setPixel(xc-y, yc+x, value);
            image.setPixel(xc+y, yc-x, value);
            image.setPixel(xc-y, yc-x, value);

    }

void MainWindow::BresenhamLine(int x1,int y1, int x2, int y2)
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
}

void MainWindow::BresenhamCircle(int x,int y,int r)
{
    int x1,y1;
    x1=0;
    y1=r;

    int x2,y2;
    int d=3-(2*r);
    while(x1<y1)
    {
    x2=x1;
    y2=y1;
    x1++;
    if(d<0)
    {
        d+=(4*x1+6);
    }
     else
    {
        y1=y1-1;
        d=d+(4*(x1-y1))+10;
    }

    printCircle(x,y,x2,y2);
    }
}


void MainWindow::on_pushButton_clicked()
{
    int x = ui->textEdit->toPlainText().toInt();
    int y= ui->textEdit_2->toPlainText().toInt();
    int r= ui->textEdit_3->toPlainText().toInt();

     BresenhamCircle(x,y,r);

     ui->label->setPixmap(QPixmap::fromImage(image));
     ui->label->show();

}

void MainWindow::on_pushButton_2_clicked()
{
    // do tp
    int x = ui->textEdit->toPlainText().toInt();
    int y= ui->textEdit_2->toPlainText().toInt();
    int r= ui->textEdit_3->toPlainText().toInt();

    BresenhamCircle(x,y,(r/2));
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
