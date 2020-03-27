#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <algorithm>
#include<bits/stdc++.h>

QImage image(300,300,QImage::Format_RGB888);
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
void dda(int x_one, int x_two, int y_one, int y_two)
{
    int value;
    value = qRgb(0,255,0);
    float length = 0;
    if(abs(x_one-x_two) >= abs(y_one-y_two))
    {
        length = abs(x_one-x_two);
    }
    else
    {
       length = abs(y_one-y_two);
    }
    float delta_x = (x_two - x_one)/length;
    float delta_y = (y_two - y_one)/length;
    float x = (x_one + 0.5);
    float y = (y_one + 0.5);
    int i = 1;
    while(i <= length)
    {
        image.setPixel(int(x),int(y),value);
        x = x + delta_x;
        y = y+ delta_y;
        i++;
    }
}
void MainWindow::on_pushButton_clicked()
{
    //for(int x=50;x<250;x++){
        //image.setPixel(x , 100 , value);
   // }
    /*QString x1 = ui->textEdit->toPlainText();
    QString x2 = ui->textEdit_2->toPlainText();
    QString y1 = ui->textEdit_3->toPlainText();
    QString y2 = ui->textEdit_4->toPlainText();

    int  x_one = x1.toInt();
    int  x_two = x2.toInt();
    int  y_one = y1.toInt();
    int  y_two = y2.toInt();

    for(int i = x_one; i <= x_two ; i++)
    {
        image.setPixel(i,100,value);
    }
    for(int i = y_one; i <= y_two ; i++)
    {
        image.setPixel(100,i,value);
    }*/
    int x_one = ui->textEdit->toPlainText().toInt();
    int x_two = ui->textEdit_2->toPlainText().toInt();
    int y_one = ui->textEdit_3->toPlainText().toInt();
    int y_two = ui->textEdit_4->toPlainText().toInt();
    dda(x_one, x_two,y_one,y_two);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();

}
int sign(int a, int b)
{
    if (a > b)
    {
        return 1;
    }
    else if (a == b)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
void bresenham(int x1, int x2, int y1,int y2)
{
    QRgb value;
    value = qRgb(0,255,0);
    int x = x1;
    int y = y1;
    int delta_x = abs(x2 - x1);
    int delta_y = abs(y2 - y1);
    int s1 = sign(x2,x1);
    int s2 = sign(y2,y1);
    int interchange = 0;
     if (delta_y > delta_x)
     {
         int tmp = delta_x;
         delta_x = delta_y;
         delta_y = tmp;
         interchange = 1;
     }

     int e_bar = (2 * delta_y) - delta_x;
     for (int i = 1; i <= delta_x; i++)
     {
        image.setPixel(x,y,value);
        while(e_bar > 0)
        {
            if (interchange == 1)
            {
                x = x + s1;
            }
            else
            {
                y = y + s2;
            }
            e_bar = e_bar - (2 * delta_x);
        }
        if(interchange == 1)
        {
            y = y + s2;
        }
        else
        {
            x = x + s1;
        }
        e_bar = e_bar + (2 * delta_y);
     }

}
void MainWindow::on_pushButton_2_clicked()
{
    int x1 = ui->textEdit->toPlainText().toInt();
    int x2 = ui->textEdit_2->toPlainText().toInt();
    int y1 = ui->textEdit_3->toPlainText().toInt();
    int y2 = ui->textEdit_4->toPlainText().toInt();
    bresenham(x1,x2,y1,y2);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();

}

void MainWindow::on_pushButton_3_clicked()
{
    int length = ui -> textEdit_5 -> toPlainText().toInt();
    int breadth = ui -> textEdit_6 -> toPlainText().toInt();
    bresenham(0,breadth,0,0);
    bresenham(0,0,0,length);
    bresenham(0,breadth,length,length);
    bresenham(breadth,breadth,0,length);
    dda(0,breadth/2,length/2,0);
    dda(breadth/2,breadth,0,length/2);
    dda(breadth/2,breadth,length,length/2);
    dda(0,breadth/2,length/2,length);
    //bresenham(0,breadth/2,length/2,0);
   // bresenham(breadth/2,breadth,0,length/2);
    //bresenham(breadth/2,breadth,length,length/2);
    //bresenham(0,breadth/2,length/2,length);

    //bresenham(breadth/4,(3*breadth)/4,length/4,length/4);
    //bresenham(breadth/4,breadth/4,length/4,(3*length)/4);
   // bresenham((3*breadth)/4,(3*breadth)/4,length/4,(length*3)/4);
    //bresenham(breadth/4,(3*breadth)/4,(3*length)/4,(3*length)/4);

    dda(breadth/4,(3*breadth)/4,length/4,length/4);
    dda(breadth/4,breadth/4,length/4,(3*length)/4);
    dda((3*breadth)/4,(3*breadth)/4,length/4,(length*3)/4);
    dda(breadth/4,(3*breadth)/4,(3*length)/4,(3*length)/4);


    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();

}
