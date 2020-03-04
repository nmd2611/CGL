#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
#include<string>
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
int counter,point[30][2],numPoints;
#define PI 3.142
void MainWindow::dda(int x1, int y1, int x2, int y2)
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
void MainWindow::on_pushButton_clicked() //Next Button
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
        ui->label_4->setText(QString("------------"));
        paint.begin((&pic));
        draw();
        paint.end();
        ui->label_5->setPicture(pic);
    }
}
void MainWindow::draw() //Drawing polygon method
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

void MainWindow::on_pushButton_2_clicked()  //Number of Points accept button
{
counter=0;
numPoints=ui->textEdit->toPlainText().toInt();
ui->pushButton->setEnabled(true);
ui->pushButton->setText(QString("NEXT POINT"));
ui->label_4->setText(QString("Point 1 Co-ordinates:"));
}

void MainWindow::on_pushButton_3_clicked() //Reflection y=x
{
    paint.begin((&pic));
    draw();
    int i=0;
    for(i=0;i<numPoints-1;i++)  //x_co=x*0+y*1
    {                           //y_co=x*1+y*0
        dda(point[i][1],point[i][0],point[i+1][1],point[i+1][0]);
    }
    dda(point[0][1],point[0][0],point[i][1],point[i][0]);
     paint.end();
     ui->label_5->setPicture(pic);
}

void MainWindow::on_pushButton_4_clicked() //Reflection about x axis
{
    paint.begin((&pic));
    draw();
    int i=0;
    for(i=0;i<numPoints-1;i++)  //x_co=x*1+y*0
    {                           //y_co=x*0+y*(-1)
        dda(point[i][0],(-1*point[i][1]),point[i+1][0],(-1*point[i+1][1]));
    }
    dda(point[0][0],(-1*point[0][1]),point[i][0],(-1*point[i][1]));
     paint.end();
     ui->label_5->setPicture(pic);
}

void MainWindow::on_pushButton_5_clicked() //reflection about y-axis
{
    paint.begin((&pic));
    draw();
    int i=0;
    for(i=0;i<numPoints-1;i++)  //x_co=x*1+y*0
    {                           //y_co=x*0+y*(-1)
        dda((-1*point[i][0]),point[i][1],(-1*point[i+1][0]),point[i+1][1]);
    }
    dda((-1*point[0][0]),point[0][1],(-1*point[i][0]),point[i][1]);
    paint.end();
    ui->label_5->setPicture(pic);
}

void MainWindow::on_pushButton_6_clicked() //Reflection about origin
{
    paint.begin((&pic));
    draw();
    int i=0;
    for(i=0;i<numPoints-1;i++)  //x_co=x*1+y*0
    {                           //y_co=x*0+y*(-1)
        dda((-1*point[i][0]),(-1*point[i][1]),(-1*point[i+1][0]),(-1*point[i+1][1]));
    }
    dda((-1*point[0][0]),(-1*point[0][1]),(-1*point[i][0]),(-1*point[i][1]));
    paint.end();
    ui->label_5->setPicture(pic);
}

void MainWindow::on_pushButton_7_clicked() //rotatiojn about arbitrary point
{
    double angle=ui->textEdit_4->toPlainText().toFloat();
    int x=ui->textEdit_2->toPlainText().toInt();
    int y=ui->textEdit_3->toPlainText().toInt();

    paint.begin((&pic));
    draw();
    int i=0;
    for(i=0;i<numPoints-1;i++)  //x_co=x*1+y*0
    {                           //y_co=x*0+y*(-1)
        dda((cos(angle*PI/180)*point[i][0])-(sin(angle*PI/180)*point[i][1])+x,(sin(angle*PI/180)*point[i][0])+(cos(angle*PI/180)*point[i][1])+y,(cos(angle*PI/180)*point[i+1][0])-(sin(angle*PI/180)*point[i+1][1])+x,(sin(angle*PI/180)*point[i+1][0])+(cos(angle*PI/180)*point[i+1][1])+y);
    }
    dda((cos(angle*PI/180)*point[0][0])-(sin(angle*PI/180)*point[0][1])+x,(sin(angle*PI/180)*point[0][0])+(cos(angle*PI/180)*point[0][1])+y,(cos(angle*PI/180)*point[i][0])-(sin(angle*PI/180)*point[i][1])+x,(sin(angle*PI/180)*point[i][0])+(cos(angle*PI/180)*point[i][1])+y);
    paint.end();
    ui->label_5->setPicture(pic);
}

void MainWindow::on_pushButton_8_clicked()
{
    paint.begin((&pic));
    draw();
    int i=0;
    for(i=0;i<numPoints-1;i++)  //x_co=x*1+y*0
    {                           //y_co=x*0+y*(-1)
        dda((2*point[i][0]),2*point[i][1],(2*point[i+1][0]),2*point[i+1][1]);
    }
    dda((2*point[0][0]),2*point[0][1],(2*point[i][0]),2*point[i][1]);
    paint.end();
    ui->label_5->setPicture(pic);
}
