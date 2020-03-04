#include "transformations.h"
#include "ui_transformations.h"
#include<math.h>
Transformations::Transformations(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Transformations)
{
    ui->setupUi(this);
}

Transformations::~Transformations()
{
    delete ui;
}
int counter,point[30][2],numPoints;

void Transformations::dda(int x1, int y1, int x2, int y2)
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
           // float ty=(y);
    paint.drawPoint(round(x)+150,150-round(y));
          //  img.setPixel(round(x)+150,150-round(y),qRgb(128,15,45));
            x=x+xinc;
            y=y+yinc;
            i++;
        }
}
void Transformations::draw() //Drawing polygon method
{
    QBrush brush;
    brush.setColor(Qt::yellow);
    paint.setBrush(brush);
    paint.setPen(Qt::red);
    paint.drawLine(QPoint(150,0),QPoint(150,300));
    paint.drawLine(QPoint(0,150),QPoint(300,150));
    int i=0;
    for(i=0;i<numPoints-1;i++)
    {
        dda(point[i][0],point[i][1],point[i+1][0],point[i+1][1]);
    }
    dda(point[0][0],point[0][1],point[i][0],point[i][1]);


}

void Transformations::on_pushButton_2_clicked()
{
    counter=0;
    numPoints=ui->textEdit->toPlainText().toInt();
    ui->pushButton->setEnabled(true);
    ui->pushButton->setText(QString("NEXT POINT"));
    ui->label_4->setText(QString("Point 1 Co-ordinates:"));
}

void Transformations::on_pushButton_clicked()
{


    QString pstr;
       if(counter<numPoints)
       {
           point[counter][0]=ui->textEdit_2->toPlainText().toInt();
           point[counter][1]=ui->textEdit_3->toPlainText().toInt();

           counter++;
         pstr="Point"+QString::number(counter+1)+" Co-ordinates";
           ui->label_4->setText(pstr);
       }
       if(counter==numPoints)
       {

           ui->pushButton->setEnabled(false);
           ui->pushButton->setText(QString("Done"));
//           ui->label_4->setText(QString("Enter tx&ty or sx&sy"));
           paint.begin((&pic));
           draw();
           paint.end();
           ui->label_5->setPicture(pic);
       }
}
void Transformations::on_translation_clicked()
{
    int tx=ui->textEdit_4->toPlainText().toInt();
    int ty=ui->textEdit_5->toPlainText().toInt();
    paint.begin((&pic));
    draw();
    int i=0;
    for(i=0;i<numPoints-1;i++)  //x_co=x*1+y*0
    {                           //y_co=x*0+y*(-1)
        dda(tx+point[i][0],(ty+point[i][1]),tx+point[i+1][0],(ty+point[i+1][1]));
    }
    dda(tx+point[0][0],(ty+point[0][1]),tx+point[i][0],(ty+point[i][1]));
     paint.end();
     ui->label_5->setPicture(pic);
}

void Transformations::on_scaling_clicked()
{
    int sx=ui->textEdit_6->toPlainText().toInt();
    int sy=ui->textEdit_7->toPlainText().toInt();
    paint.begin((&pic));
    draw();
    int i=0;
    for(i=0;i<numPoints-1;i++)  //x_co=x*1+y*0
    {                           //y_co=x*0+y*(-1)
        dda(sx*point[i][0],(sy*point[i][1]),sx*point[i+1][0],(sy*point[i+1][1]));
    }
    dda(sx*point[0][0],(sy*point[0][1]),sx*point[i][0],(sy*point[i][1]));
     paint.end();
     ui->label_5->setPicture(pic);
}

void Transformations::on_rotation_clicked()
{
    double angle=ui->angleEdit->toPlainText().toDouble();

    angle=angle*3.142/180;

    paint.begin((&pic));
    draw();
    int i=0;
    for(i=0;i<numPoints-1;i++)  //x_co=x*1+y*0
    {                           //y_co=x*0+y*(-1)
        dda(cos(angle)*point[i][0]-sin(angle)*point[i][1],(sin(angle)*point[i][0])+cos(angle)*point[i][1],cos(angle)*point[i+1][0]-sin(angle)*point[i+1][1],(sin(angle)*point[i+1][0])+cos(angle)*point[i+1][1]);
    }
    dda(cos(angle)*point[0][0]-sin(angle)*point[0][1],(sin(angle)*point[0][0])+cos(angle)*point[0][1],  cos(angle)*point[i][0]-sin(angle)*point[i][1],(sin(angle)*point[i][0])+cos(angle)*point[i][1]);
     paint.end();
     ui->label_5->setPicture(pic);
}
