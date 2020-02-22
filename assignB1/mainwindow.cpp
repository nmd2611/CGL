#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include<bits/stdc++.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
QImage image(500,500,QImage::Format_RGB888);
QRgb value = qRgb(0,255,0);

MainWindow::~MainWindow()
{
    delete ui;
}

void DDALine(int x1,int y1, int x2, int y2,int choice)
{
    float x,y;
    int dx,dy;

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
    int cnt=0;
    while(steps--)
    {
        if(choice == 1)
           { if(cnt % 2 == 0)
             image.setPixel(x,y,value);  //draws pixel with value
            }
        else if(choice == 2)
        {
            if(cnt % 5 == 0 || cnt % 5 == 1 || cnt % 5 == 2)
            {
            }
            else
                image.setPixel(x,y,value);
        }
        else if(choice == 3)
        {
            if(cnt % 6 == 0  || cnt % 6 == 3 || cnt % 6 == 4)
            {
            }
            else
                image.setPixel(x,y,value);
        }
        else
            image.setPixel(x,y,value);
        //print pixel
        x+= xinc;
        y+= yinc;
        cnt++;
    }
}


void MainWindow::on_pushButton_clicked()
{
    // solid

    int x1= ui->textEdit->toPlainText().toInt();
    int y1 =ui->textEdit_2->toPlainText().toInt();

    int x2=ui->textEdit_3->toPlainText().toInt();
    int y2=ui->textEdit_4->toPlainText().toInt();
    int choice=0;
    DDALine(x1,y1,x2,y2,choice);

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    // dotted

    int x1= ui->textEdit->toPlainText().toInt();
    int y1 =ui->textEdit_2->toPlainText().toInt();

    int x2=ui->textEdit_3->toPlainText().toInt();
    int y2=ui->textEdit_4->toPlainText().toInt();
    int choice=1;
    DDALine(x1,y1,x2,y2,choice);

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}



void MainWindow::on_pushButton_3_clicked()
{
    // dashed

    int x1= ui->textEdit->toPlainText().toInt();
    int y1 =ui->textEdit_2->toPlainText().toInt();

    int x2=ui->textEdit_3->toPlainText().toInt();
    int y2=ui->textEdit_4->toPlainText().toInt();
    int choice=2;
    DDALine(x1,y1,x2,y2,choice);

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    // dashed dot

    int x1= ui->textEdit->toPlainText().toInt();
    int y1 =ui->textEdit_2->toPlainText().toInt();

    int x2=ui->textEdit_3->toPlainText().toInt();
    int y2=ui->textEdit_4->toPlainText().toInt();
    int choice=3;
    DDALine(x1,y1,x2,y2,choice);

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    // thick

    int x1= ui->textEdit->toPlainText().toInt();
    int y1 =ui->textEdit_2->toPlainText().toInt();

    int x2=ui->textEdit_3->toPlainText().toInt();
    int y2=ui->textEdit_4->toPlainText().toInt();

    int width=ui->textEdit_5 ->toPlainText().toInt();
    int choice=4;
    width/=2;
    int nx,ny;
    int vx,vy;

    nx=x1;
    ny=y1;

    vx=x2;
    vy=y2;
    while(width--)
    {
         DDALine(nx--,ny--,vx--,vy--,choice);
         DDALine(x1++,y1++,x2++,y2++,choice);
    }


    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}