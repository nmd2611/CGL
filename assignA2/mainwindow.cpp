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
    QRgb value=qRgb(0,255,0);;     //set the colour value


    void printCircle(int xc, int yc, int x, int y)
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

void BresenhamCircle(int x,int y,int r)
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
}
