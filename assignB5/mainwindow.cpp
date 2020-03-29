#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::HilbertCurve(int u,int r,int d, int l, int h,int i,int& x,int& y)
{
    if(i<=0)
    {
        return;
    }
    i--;
    HilbertCurve(r,u,l,d,h,i,x,y);
    move(u,h,x,y);
    HilbertCurve(u,r,d,l,h,i,x,y);
    move(r,h,x,y);
    HilbertCurve(u,r,d,l,h,i,x,y);
    move(d,h,x,y);
    HilbertCurve(l,d,r,u,h,i,x,y);

}


void MainWindow::move(int j,int h,int& x,int& y)
{
    int x1=x,y1=y;
    switch(j)
    {

    case 1:
        y-=h; //up
        break;
    case 2:
        x+=h;  //right
        break;
    case 4:
        x-=h;  //left

        break;
    case 3 :
        y+=h;
        break;

    }
    DDALine(x1,y1,x,y);
}


void MainWindow::DDALine(int x1,int y1, int x2, int y2)
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
    int x=200,y=500;
    HilbertCurve(1,2,3,4,5,6,x,y);


    ui->label_2->setPixmap(QPixmap::fromImage(image));
    ui->label_2->show();
}


