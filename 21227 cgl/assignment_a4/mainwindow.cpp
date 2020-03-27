#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include<QMouseEvent>
#include <algorithm>
#include <bits/stdc++.h>
bool flag = 1;
int arrx[50]={0};
int arry[50]={0};
int i = 0;
QRgb value = qRgb(0,255,0);
QImage image(300,300,QImage::Format_RGB888);
QImage image_color(25,25,QImage::Format_RGB888);
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
void MainWindow::mousePressEvent(QMouseEvent *m)
{
    int x,y;
    if(flag == 1)
    {
        if(m -> button() == Qt::RightButton)
        {
            flag = 0;
            bresenham(arrx[i-1],arrx[0],arry[i-1],arry[0]);
            goto label;
        }
        else
        {
            x = m -> pos().x();
            y = m -> pos().y();
            //image.setPixel(x,y,value);
            arrx[i] = x;
            arry[i] = y;
            if(i)
            {
                bresenham(arrx[i-1],x,arry[i-1],y);
            }
            label:
            ui -> label -> setPixmap(QPixmap::fromImage(image));
            ui->label->show();
            i++;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    int r =  ui->horizontalSlider->value();
    int g =  ui->horizontalSlider_2->value();
    int b =  ui->horizontalSlider_3->value();
    value = qRgb(r,g,b);
    for(int i = 0 ; i < 25 ; i++)
    {
        for(int j = 0;j<25;j++)
        {
            image_color.setPixel(i,j,value);
        }
    }
    ui -> label2 -> setPixmap(QPixmap::fromImage(image_color));
    ui->label2->show();
}
