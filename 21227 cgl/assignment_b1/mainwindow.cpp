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
void dda(int x_one, int x_two, int y_one, int y_two, int choice)
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
        bool set = 1;
        switch(choice)
        {
        case 1: set =1;
            break;
        case 2:set = int(i)%2;
            break;
        case 3:set = (i%4);
            break;
        case 4:
            if(i%6 != 4 && i%6 != 0)
            {
                set = 1;
            }
            else{
                set = 0;
            }
            break;
        default:{}
        }

        if(set == 1)
        {
            image.setPixel(int(x),int(y),value);
        }
        x = x + delta_x;
        y = y+ delta_y;
        i++;
    }
}
void MainWindow::on_pushButton_clicked()
{
    int x_one = ui->textEdit->toPlainText().toInt();
    int x_two = ui->textEdit_2->toPlainText().toInt();
    int y_one = ui->textEdit_3->toPlainText().toInt();
    int y_two = ui->textEdit_4->toPlainText().toInt();
    int choice = 1;
    dda(x_one, x_two,y_one,y_two,choice);
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
    int choice = 2;
    dda(x1,x2,y1,y2,choice);
    //bresenham(x1,x2,y1,y2);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    int x1 = ui->textEdit->toPlainText().toInt();
    int x2 = ui->textEdit_2->toPlainText().toInt();
    int y1 = ui->textEdit_3->toPlainText().toInt();
    int y2 = ui->textEdit_4->toPlainText().toInt();
    int choice = 3;
    dda(x1,x2,y1,y2,choice);
    //bresenham(x1,x2,y1,y2);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    int x1 = ui->textEdit->toPlainText().toInt();
    int x2 = ui->textEdit_2->toPlainText().toInt();
    int y1 = ui->textEdit_3->toPlainText().toInt();
    int y2 = ui->textEdit_4->toPlainText().toInt();
    int choice = 4;
    dda(x1,x2,y1,y2,choice);
    //bresenham(x1,x2,y1,y2);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    int x1 = ui->textEdit->toPlainText().toInt();
    int x2 = ui->textEdit_2->toPlainText().toInt();
    int y1 = ui->textEdit_3->toPlainText().toInt();
    int y2 = ui->textEdit_4->toPlainText().toInt();
    int width = ui->textEdit_5->toPlainText().toInt();
    int choice = 1;
    int w = width/2;
    int y1_tmp = y1;
    int y2_tmp = y2;
    int x1_tmp = x1;
    int x2_tmp = x2;
    float slope;
    if(x1 == x2)
    {
        slope= 2;
    }
    else
    {
        slope= (y2-y1)/(x2-x1);
    }
    if(slope <= 1)
    {
        while(w--)
        {
            dda(x1,x2,y1_tmp++,y2_tmp++,choice);
        }
        w = width/2;
        while(w--)
        {
            dda(x1,x2,y1_tmp--,y2_tmp--,choice);
        }
    }
    else
    {
        while(w--)
        {
            dda(x1_tmp++,x2_tmp++,y1,y2,choice);
        }
        w = width/2;
        while(w--)
        {
            dda(x1_tmp--,x2_tmp--,y1,y2,choice);
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
