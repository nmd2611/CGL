#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>

int counter,point[30][2],numPoints;
 QImage img(400,300,QImage::Format_RGB32);
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
    img.setPixel(round(x)+150,150-round(y),qRgb(255, 255, 255));
          //  img.setPixel(round(x)+150,150-round(y),qRgb(128,15,45));
            x=x+xinc;
            y=y+yinc;
            i++;
        }
         img.setPixel(150,150,qRgb(255, 255, 255));
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
      //  paint.begin((&pic));
        draw();
       // paint.end();
      ui->label_5->setPixmap(QPixmap::fromImage(img));
        //  ui->label_5->setPicture(pic);
    }
}
void MainWindow::draw() //Drawing polygon method
{

  //  paint.setBrush(brush);
   // paint.setPen(Qt::red);
   // paint.drawLine(QPoint(150,0),QPoint(150,300));
   // paint.drawLine(QPoint(0,150),QPoint(300,150));
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
void flodfill(int x,int y,QRgb  b)
{
    QColor clr;
    //clr=img.pixel(x,y);
    if(img.pixel(x,y)!=b && img.pixel(x,y)!=qRgb(255,0,0))
    {

        //img.setColor();
        img.setPixel(x,y,qRgb(255,0,0));
        flodfill(x+1,y,b);
        flodfill(x,y-1,b);
        flodfill(x,y+1,b);
        flodfill(x-1,y,b);
//        flodfill(x,y+1,b);
//        flodfill(x+1,y+1,b);
//        flodfill(x-1,y-1,b);
//        flodfill(x-1,y,b);
//        flodfill(x,y-1,b);
//        flodfill(x-1,y+1,b);
//        flodfill(x+1,y-1,b);
    }
   //  img.setPixel(x,y,qRgb(255,255,255));
}
void MainWindow::on_pushButton_3_clicked()
{
    int x=150+ui->textEdit_2->toPlainText().toInt(); //seed point
    int y=150-ui->textEdit_3->toPlainText().toInt();
  //  QColor back=img.pixel(290,290);
    flodfill(x,y,qRgb(255,255,255) );
     ui->label_5->setPixmap(QPixmap::fromImage(img));
}

