#include "poly.h"
#include "ui_poly.h"

Poly::Poly(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Poly)
{
    ui->setupUi(this);
    nl=new drawingLabel(this);
    nl->setText(QString("Drawing Area"));
    nl->setObjectName(QString("drawingArea"));
    nl->setFrameShape(QFrame::Box);
    nl->setMinimumSize(901,437);
    nl->setMouseTracking(true);
    image=QImage(901,437,QImage::Format_RGB888);
    fillColor=qRgb(0,0,255);
    nl->setPixmap(QPixmap::fromImage(image));
    connect(nl,&drawingLabel::Mouse_Click,this,&Poly::mousePressed);
    connect(nl,&drawingLabel::Mouse_RecordStart,this,&Poly::showFirstPoint);
    connect(nl,&drawingLabel::Mouse_Hover,this,&Poly::mouseHover);
    connect(nl,&drawingLabel::Mouse_DClick,this,&Poly::seedFill);
    nl->show();
}
Poly::~Poly()
{
    delete ui;
}
void Poly::draw_line(int x1,int y1,int x2,int y2,int red,int green,int blue)
{
    double len;
    if (abs(x2-x1)>=abs(y2-y1))
        len=abs(x2-x1);
    else
        len=abs(y2-y1);
    double X=(x2-x1)/len;
    double Y=(y2-y1)/len;
    double x=x1+(0.5*sign(X));
    double y=y1+(0.5*sign(Y));
    int i=1;
    while(i<=len)
    {
        image.setPixel(x,y,qRgb(red,green,blue));
        x=x+X;
        y=y+Y;
        i+=1;
     }
}
int Poly::sign(int a)
{
    if(a<0)
        return -1;
    else if(a>0)
        return 1;
    else
        return 0;

}
void Poly::mousePressed()
{
    //ui->setText("Mouse Pressed!");
    draw_line(nl->X1,nl->Y1,nl->X2,nl->Y2,255,255,255);
    nl->setPixmap(QPixmap::fromImage(image));
}
void Poly::showFirstPoint()
{
    ui->startPointWindow->setText(QString("Polygon Start Point (X=%1,Y=%2)").arg(nl->x).arg(nl->y));
}
void Poly::mouseHover()
{
    ui->mousePos->setText(QString("X=%1,Y=%2").arg(nl->x).arg(nl->y));
}
void Poly::on_pushButton_4_clicked()
{
    fillColor=qRgb(0,255,255);
}
void Poly::on_pushButton_5_clicked()
{
    fillColor=qRgb(255,255,0);
}
void Poly::on_pushButton_clicked()
{
    fillColor=qRgb(255,0,0);
}
void Poly::on_pushButton_2_clicked()
{
    fillColor=qRgb(0,255,0);
}
void Poly::on_pushButton_3_clicked()
{
    fillColor=qRgb(0,0,255);
}
void Poly::seedFill()
{
    //QRgb value=qRgb(255,255,255);
    s.push(nl->x);
    s.push(nl->y);
    while(!s.empty())
    {
       int y=s.top();
       s.pop();
       int x=s.top();
       s.pop();
       QRgb currentPixel=image.pixel(x,y);
       if(currentPixel!=qRgb(255,255,255) && currentPixel!=fillColor)
       {
         image.setPixel(x,y,fillColor);
         s.push(x+1);s.push(y);
         s.push(x);s.push(y+1);
         s.push(x-1);s.push(y);
         s.push(x);s.push(y-1);
       }
    }
     nl->setPixmap(QPixmap::fromImage(image));

}
