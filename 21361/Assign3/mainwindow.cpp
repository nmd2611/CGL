#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "QColorDialog"
#include <cmath>
QImage img(600,600,QImage::Format_RGB888);
QImage img1(100,100,QImage::Format_RGB32);
QColor color,color1;
QRgb value,value1;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver=0;
    start=true;
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(start)
    {
        int p=ev->pos().x();
        int q=ev->pos().y();
        a[ver]=p;
        b[ver]=q;
        if(ev->button()==Qt::RightButton)
        {
            dda(a[ver],b[ver],a[0],b[0]);
            value = qRgb(0, 0, 255);
            value1 = qRgb(255, 255, 0);
            Flood_fill(a[0],b[0],value,value1);
            start=false;
        }
        else
        {
            if(ver>0)
            {
                dda(a[ver],b[ver],a[ver-1],b[ver-1]);
            }
        }
        ver++;
    }

}



void MainWindow:: dda(int x1,int y1,int x2,int y2)
{
    float dx,dy,len,xinc,yinc,x,y;
    int i;
    dx=x2-x1;
    dy=y2-y1;
    if(abs(dx)>=abs(dy))
        len=abs(dx);
    else
        len=abs(dy);
    xinc=dx/len;
    yinc=dy/len;
    x=x1,y=y1,i=0;
    while(i<len)
    {
        img.setPixel(x,y,color.rgb());
        x=x+xinc;
        y=y+yinc;
        i++;
    }
     ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::Flood_fill(int x,int y,QRgb fillcolor,QRgb bkcolor)
{
    if(img.pixel(x,y) == bkcolor)
    {
        img.setPixel(x,y,fillcolor);
        Flood_fill(x+1,y,fillcolor,bkcolor);
        Flood_fill(x,y+1,fillcolor,bkcolor);
        Flood_fill(x-1,y,fillcolor,bkcolor);
        Flood_fill(x,y-1,fillcolor,bkcolor);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    color=QColorDialog::getColor();
}
