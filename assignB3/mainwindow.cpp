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

MainWindow::~MainWindow()
{
    delete ui;
}

QImage image(700,700,QImage::Format_RGB888);
QRgb value = qRgb(0,255,0);
QRgb value2 = qRgb(0,255,255);

// set window attributes

 int Left=1,Right=2,Top=8,Bottom=4,inside=0;
 int xmin=150,ymin=150,xmax=500,ymax=500;

void MainWindow::DDALine(int x1,int y1, int x2, int y2, QRgb mycolor)
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
        image.setPixel(x,y,mycolor);  //draws pixel with value
        //print pixel
        x+= xinc;
        y+= yinc;
    }
}


void MainWindow::mousePressEvent(QMouseEvent *ev)
{
if(ev->button() == Qt::LeftButton && flag == 0)
{
     x[i]=ev->pos().x()-60 ;
     y[i]=ev->pos().y() +30;

     if(i != 0)
        DDALine(x[i-1],y[i-1],x[i],y[i],value2);
   // image.setPixel(x[i],y[i],value);
    i++;
}

if(ev->button() == Qt::RightButton && flag == 0)
{
    flag=1;
    DDALine(x[i-1],y[i-1],x[0],y[0],value2);
}
ui->label->setPixmap(QPixmap::fromImage(image));
ui->label->show();
}



int MainWindow::code(int x1,int y1)
{
    int c=inside;
    if(x1<xmin)
    {
        c=c | Left;
    }
   else if(x1>xmax)
    {
        c= c | Right;
    }
    if(y1<ymin)
    {
        c=c | Bottom;
    }
    else if(y1>ymax)
    {
        c=c | Top;
    }
    return c;
}

void MainWindow::Cohen(int x1,int y1,int x2,int y2)
{
int code1=code(x1,y1),code2=code(x2,y2);
int a=x1,b=y1,c=x2,d=y2;
bool accept=false;
while(true)
{
    if(code1==0 && code2==0)
    {
        accept=true;
        break;
    }
    else if(code1 & code2)
    {
        break;
    }
    else
    {
        int codeout;
        if(code1!=0)
        {
            codeout=code1;
        }
        else
        {
            codeout=code2;
        }

        double X,Y;
        if(codeout & Top)
        {
            Y=ymax;
            X=x1+double((x2-x1)*(ymax-y1)/(y2-y1));
        }
        else if(codeout & Bottom)
        {
            Y=ymin;
            X=x1+double((ymin-y1)*(x2-x1)/(y2-y1));
        }
        else if(codeout & Left)
        {
            X=xmin;
            Y=y1+double((xmin-x1)*(y2-y1)/(x2-x1));
        }
        else if(codeout & Right)
        {
            X=xmax;
            Y=y1+double((xmax-x1)*(y2-y1)/(x2-x1));
        }
        if(codeout==code1)
        {
            x1=X;
            y1=Y;
            code1=code(x1,y1);
        }
        else
        {
            x2=X;
            y2=Y;
            code2=code(x2,y2);
        }
    }
}

if(accept)
{
    QRgb old=qRgb(0,0,0);
    DDALine(a,b,c,d,old);
    QRgb ne=qRgb(0,0,255);
    DDALine(x1,y1,x2,y2,ne);
}

ui->label->setPixmap(QPixmap::fromImage(image));
ui->label->show();

}

void MainWindow::on_pushButton_clicked()
{
    // polygon clip

    // specify the size of window

   // cout<<x1<<y1<<x2<<y2<<endl;

    for(int j=1;j<i;j++)
        Cohen(x[j],y[j],x[j-1],y[j-1]);
    Cohen(x[0],y[0],x[i-1],y[i-1]);
}

void MainWindow::on_pushButton_2_clicked()
{
     int x1,y1,x2,y2;
    x1=150; y1=150;
    x2=500; y2= 500;
    //image.setPixel(x1,y1,value2);
   // image.setPixel(x2,y2,value2);
    QRgb val = qRgb(255,0,255);
    DDALine(x1,y1,x1,y2,val);
    DDALine(x1,y2,x2,y2,val);
    DDALine(x2,y2,x2,y1,val);
    DDALine(x2,y1,x1,y1,val);

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
