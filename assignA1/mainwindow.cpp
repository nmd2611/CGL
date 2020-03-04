#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include<bits/stdc++.h>
#include<math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage image(700,700,QImage::Format_RGB888);
QRgb value = qRgb(0,255,0);
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


void BresenhamLine(int x1,int y1, int x2, int y2)
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

void DDALine(int x1,int y1, int x2, int y2)
{
    float x,y;
    float dx,dy;

    dx=x2-x1;     // Calculating dx
    dy=y2-y1;     // Calculating dy

    int steps=(abs(dx)>abs(dy))?abs(dx):abs(dy);

    float xinc,yinc;

    if(steps != 0)          // Calculating Xinc and Yinc
    {
         xinc= dx/ steps;
         yinc= dy/ steps;
    }

    x=x1+0.5;
    y=y1+0.5;
    while(steps--)
    {
        image.setPixel(x,y,value);  //draws pixel with value
        //print pixel
        x+= xinc;
        y+= yinc;
    }
}
void MainWindow::on_pushButton_clicked()
{
    // create pattern

//    BresenhamLine(200,400,600,400);
//    BresenhamLine(600,200,600,400);
//    BresenhamLine(200,200,600,200);
//    BresenhamLine(200,200,200,400);

    DDALine(200,400,600,400);
    DDALine(600,200,600,400);
    DDALine(200,200,600,200);
    DDALine(200,200,200,400);

    ui->label_3->setPixmap(QPixmap::fromImage(image));
    ui->label_3->show();
}

