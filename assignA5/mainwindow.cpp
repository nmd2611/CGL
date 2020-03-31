#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include "QMouseEvent"
#include "QColorDialog"
#include <cmath>
#include<bits/stdc++.h>
using namespace std;

QImage image(900,900,QImage::Format_RGB888);
QImage image2(900,900,QImage::Format_RGB888);
QImage clear(900,900,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}




QRgb value = qRgb(0,255,0);

QRgb value2 = qRgb(255,0,255);

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
if(ev->button() == Qt::LeftButton)
{
    float p,q;
     p=ev->pos().x() - 40;
     q=ev->pos().y() + 80;
     image.setPixel(p,q,value);

     cout<<p<<"\t"<<q<<endl;
     ui->label->setPixmap(QPixmap::fromImage(image));
    // ui->label->show();
}}


void DDALine(float x1,float y1, float x2, float y2, QImage &img)
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
        img.setPixel(x,y,value);  //draws pixel with value
        //print pixel
        x+= xinc;
        y+= yinc;
    }
}

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


    int a=200,b=200;

    int inc=100;
    int len=400;

    for(int i=0;i<5;i++)
    {
        b=200;
        for(int j=0;j<5;j++)
        {
            x[i][j]=a;
            y[i][j]=b;
            b+=inc;
        }
        a+=inc;
    }
// plotting the points of chessboard
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            image.setPixel(x[i][j],y[i][j],value);

// drawing the actual chessboard
    // lines parallel to y-axis

    int i,j;
    for(i=0;i<5;i++)
        for(j=0;j<4;j++)
            DDALine(x[i][j],y[i][j],x[i][j+1],y[i][j+1],image);

    // lines parallel to x-axis
    for(i=0;i<4;i++)
        for(j=0;j<5;j++)
            DDALine(x[i][j],y[i][j],x[i+1][j],y[i+1][j],image);


    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
    // draw outer frame
    //BresenhamLine(x1,y1,x2,y1);
   // BresenhamLine(x1,y1,x1,y2);
   // BresenhamLine(x2,y1,x2,y2);
   // BresenhamLine(x1,y2,x2,y2);

}

void MainWindow::rotatePolygon()
{

    float angle = 3.142 / 4;
for(int i=0;i<5;i++)
    for(int j=0;j<5;j++)
    {
        int X = x[i][j];
        int Y = y[i][j];
        x[i][j]= X*cos(angle) - Y*sin(angle);
        y[i][j] = X*sin(angle) + Y*cos(angle);

        // to get the chessboard near its original position , we need to subtract certain values
        x[i][j] = x[i][j] + 350;
        y[i][j] = y[i][j] - 140;
    }

for(int i=0;i<5;i++)
    for(int j=0;j<5;j++)
        image.setPixel(x[i][j],y[i][j],value2);

// drawing the actual chessboard
    // lines parallel to y-axis in actual
int i,j;
for(i=0;i<5;i++)
    for(j=0;j<4;j++)
        DDALine(floor(x[i][j]),floor(y[i][j]),floor(x[i][j+1]),floor(y[i][j+1]),image);

// lines parallel to x-axis in actual
for(i=0;i<4;i++)
    for(j=0;j<5;j++)
        DDALine(floor(x[i][j]),floor(y[i][j]),floor(x[i+1][j]),floor(y[i+1][j]),image);

ui->label->setPixmap(QPixmap::fromImage(image));
ui->label->show();
}

void MainWindow::FloodFill(float x, float y,QRgb q)
{
    cout<<"Flood"<<endl;
if(image.pixel(x,y) == q)
{
    image.setPixel(x,y,value);
    FloodFill(x,y+1,q);
    FloodFill(x,y-1,q);
    FloodFill(x+1,y,q);
    FloodFill(x-1,y,q);
}
}


void MainWindow::fillPolygon()
{
    QRgb q= qRgb(0,0,0);

    FloodFill(345,217,q);
    FloodFill(216,349,q);
    FloodFill(209,496,q);
    FloodFill(364,363,q);
    FloodFill(514,361,q);
    FloodFill(357,491,q);
    FloodFill(497,499,q);
    FloodFill(350,646,q);

    // FloodFill((x[0][0]+x[0][1])/2 + 2 , (y[0][0]+y[1][0])/2 + 2  , q);
     // FloodFill((x[0][1]+x[0][2])/2 +2 , (y[1][1]+y[0][1])/2 + 2 , q);
   // image.setPixel((x[0][1]+x[0][2])/2 + 10 , (y[0][1]+y[1][1])/2  + 10 ,value);
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_clicked()
{
    image = clear;
    // draw
    //image.setPixel(150,550,value);
   // image.setPixel(550,150,value);
    //BresenhamLine(150,550,550,550);
    //BresenhamLine(150,550,150,150);
    //BresenhamLine(550,550,550,150);
    drawPolygon();
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_2_clicked()
{
    // rotate
    image=clear;
    rotatePolygon();

}

void MainWindow::on_pushButton_3_clicked()
{
    // fill colour
    fillPolygon();
    ui->label->setPixmap(QPixmap::fromImage(image));

}



