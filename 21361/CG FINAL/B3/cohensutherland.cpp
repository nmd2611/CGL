#include "cohensutherland.h"
#include "ui_cohensutherland.h"
#include"newlabel.h"
#include<iostream>
CohenSutherland::CohenSutherland(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CohenSutherland)
{
    ui->setupUi(this);
    Xmin=250;
    Ymin=120;
    Xmax=691;
    Ymax=411;
    nl=new newLabel(this);
    image=QImage(931,531,QImage::Format_RGB888);
    nl->setMouseTracking(true);
    nl->setMinimumSize(931,531);
    nl->setFrameShape(QFrame::Box);
    draw_line(Xmin,Ymin,Xmax,Ymin,0,0,255);
    draw_line(Xmin,Ymax,Xmax,Ymax,0,0,255);
    draw_line(Xmin,Ymin,Xmin,Ymax,0,0,255);
    draw_line(Xmax,Ymin,Xmax,Ymax,0,0,255);
    nl->setPixmap(QPixmap::fromImage(image));
    connect(nl,&newLabel::FirstPoint,this,&CohenSutherland::firstPointHandler);
    connect(nl,&newLabel::SecondPoint,this,&CohenSutherland::secondPointHandler);
}
CohenSutherland::~CohenSutherland()
{
    delete ui;
}
void CohenSutherland::firstPointHandler()
{
    nl->regionFirstPoint=decideRegion(nl->x1,nl->y1);
}
void CohenSutherland::secondPointHandler()
{
    nl->regionSecondPoint=decideRegion(nl->x2,nl->y2);
    nl->setPixmap(QPixmap::fromImage(image));
    CohenSutherlandLineClipping();
}
void CohenSutherland::CohenSutherlandLineClipping()
{
    if(!(nl->regionFirstPoint || nl->regionSecondPoint))
    {
        draw_line(nl->x1,nl->y1,nl->x2,nl->y2,255,0,0);
        nl->setPixmap(QPixmap::fromImage(image));
        ui->label_3->setText(QString("Line Completely Visible"));
        return;
    }
    int output=nl->regionFirstPoint & nl->regionSecondPoint;
    if(output)
    {
        ui->label_3->setText(QString("Line Completely Invisible"));
        return;
    }
    else
    {
        int TOP=8,BOTTOM=4,RIGHT=2,LEFT=1;
        int XL=Xmin,XR=Xmax,YT=Ymin,YB=Ymax;
        double m=(double)(nl->y2-nl->y1)/(nl->x2-nl->x1);

        int x1=0,y1=0;
        ui->label_3->setText(QString("Line Partially Visible"));
        if(nl->regionFirstPoint!=0)
        {
            if(nl->regionFirstPoint & TOP)
            {
                x1=nl->x1+((1/m)*(YT-nl->y1));
                y1=YT;
            }
            else if(nl->regionFirstPoint & BOTTOM)
            {
                x1=nl->x1+((1/m)*(YB-nl->y1));
                y1=YB;
            }
            else if(nl->regionFirstPoint & RIGHT && m!=0)
            {
                x1=XR;
                y1=m*(XR-nl->x1)+nl->y1;
            }
            else if(nl->regionFirstPoint & LEFT)
            {
                x1=XL;
                y1=m*(XL-nl->x1)+nl->y1;
            }
        }
        else
        {
            x1=nl->x1;
            y1=nl->y1;
        }
        int x2=0,y2=0;
        if(nl->regionSecondPoint!=0)
        {
            if(nl->regionSecondPoint & TOP)
            {
                x2=nl->x2+((1/m)*(YT-nl->y2));
                y2=YT;
            }
            else if(nl->regionSecondPoint & BOTTOM)
            {
                x2=nl->x2+((1/m)*(YB-nl->y2));
                y2=YB;
            }
            else if(nl->regionSecondPoint & RIGHT && m!=0)
            {
                x2=XR;
                y2=m*(XR-nl->x2)+nl->y2;
            }
            else if(nl->regionSecondPoint & LEFT)
            {
                x2=XL;
                y2=m*(XL-nl->x2)+nl->y2;
            }
        }
        else
        {
            x2=nl->x2;
            y2=nl->y2;
        }
        draw_line(x1,y1,x2,y2,255,0,0);
    }
    nl->setPixmap(QPixmap::fromImage(image));
}

short CohenSutherland::decideRegion(int x, int y)
{
    short int outcode=0;
    if(x>=Xmin && x<=Xmax && y>=Ymin && y<=Ymax)
        return 0;
    if(x<Xmin)
        outcode|=1;
    if(y<Ymin)
        outcode|=8;
    if(x>Xmax)
        outcode|=2;
    if(y>Ymax)
        outcode|=4;
    return outcode;
}
void CohenSutherland::draw_line(int x1,int y1,int x2,int y2,int red,int green,int blue)
{
    int dx=(x2-x1);
    int dy=(y2-y1);
    int length;
    float x,y;
    if(abs(dx)>=abs(dy))
        length=abs(dx);
    else
        length=abs(dy);

    float xinc=dx/float(length);
    float yinc=dy/float(length);

    x=x1;
    y=y1;
    int i=1;
    while(i<=length)
    {
        image.setPixel(round(x),round(y),qRgb(red,green,blue));
        x=x+xinc;
        y=y+yinc;
        i++;
    }
}
int CohenSutherland::sign(int a)
{
    if(a<0)
        return -1;
    else if(a>0)
        return 1;
    else
        return 0;
}
