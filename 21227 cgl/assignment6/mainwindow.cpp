#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include<QMouseEvent>
#include <algorithm>
#include <bits/stdc++.h>
#include <QStack>
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int TOP = 4; // 0100
const int BOTTOM = 8;    // 1000
int x_max;
int y_max;
int x_min;
int y_min ;
bool flag = 0;
QRgb value = qRgb(0,255,0);
bool line = 1;
QImage image(300,300,QImage::Format_RGB888);
QImage image_tmp(300,300,QImage::Format_RGB888);
QImage image_color(25,25,QImage::Format_RGB888);
class Line{
public:
    int x1,y1,y2,x2;
    Line(){
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
    }
    Line(int a, int b, int c, int d){
        x1 = a;
        y1 = b;
        x2 = c;
        y2 = d;
    }
};
Line* tmp;
QStack <Line*> l;
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
int computeCode(int x, int y){
    int code = INSIDE;
    if (x < x_min)
        code |= LEFT;
    else if(x > x_max)
        code |= RIGHT;
    if(y < y_min)
        code |= BOTTOM;
    else if(y > y_max)
        code |= TOP;
    return code;
}
QStack <Line*> final;
void cohenSutherlandClip(int x1, int y1,int x2, int y2)
{

    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    while (true)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            tmp = new Line(x1,y1,x2,y2);
            final.push(tmp);
            tmp = NULL;
            break;
        }
        else if (code1 & code2 )//&& code1 != 0 && code2 != 0)
        {
            break;
        }
        else
        {
            int code_out;
            double x, y;
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            if (code_out & TOP)
            {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }
            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
            tmp = new Line(x1,y1,x2,y2);
            final.push(tmp);
            tmp = NULL;
        }
    }
}
void dda(int x_one, int y_one, int x_two, int y_two,QImage &tmp)
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
        tmp.setPixel(int(x),int(y),value);
        x = x + delta_x;
        y = y+ delta_y;
        i++;
    }
}
int x_1 = 0,y_1 = 0,x_2 = 0,y_2 = 0;
void MainWindow::mousePressEvent(QMouseEvent *m)
{
    if(line == 0){
    x_1 = m -> pos().x();
    y_1 = m -> pos().y();
    flag = 1;
    }
    else
    {
        x_1 = m -> pos().x();
        y_1 = m -> pos().y();
        tmp = new Line;
        tmp -> x1 = x_1;
        tmp -> y1 = y_1;

    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *m)
{
    if(line == 0){
    flag = 0;
    x_2 = m -> pos().x();
    y_2 = m -> pos().y();
    dda(x_1,y_1,x_2,y_1,image);
    dda(x_1,y_1,x_1,y_2,image);
    dda(x_2,y_1,x_2,y_2,image);
    dda(x_1,y_2,x_2,y_2,image);
    int x_max = x_2;
    int y_max = y_2;
    int x_min = x_1;
    int y_min = y_1;
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui -> label -> show();
    }
    else
    {

        x_2 = m -> pos().x();
        y_2 = m -> pos().y();
        tmp -> x2 = x_2;
        tmp -> y2 = y_2;
        l.push(tmp);
        tmp = NULL;
        dda(x_1,y_1,x_2,y_2,image);
        ui->label->setPixmap(QPixmap::fromImage(image));
        ui -> label -> show();
    }
}
void MainWindow:: mouseMoveEvent(QMouseEvent *m)
{
    if(flag == 1){
    image_tmp = image;
    x_2 = m -> pos().x();
    y_2 = m -> pos().y();
    dda(x_1,y_1,x_2,y_1,image_tmp);
    dda(x_1,y_1,x_1,y_2,image_tmp);
    dda(x_2,y_1,x_2,y_2,image_tmp);
    dda(x_1,y_2,x_2,y_2,image_tmp);
    ui->label->setPixmap(QPixmap::fromImage(image_tmp));
    ui -> label -> show();
    }
    else
    {
        x_2 = m -> pos().x();
        y_2 = m -> pos().y();
        image_tmp = image;
        dda(x_1,y_1,x_2,y_2,image_tmp);
        ui->label->setPixmap(QPixmap::fromImage(image_tmp));
        ui -> label -> show();
    }
}

void MainWindow::on_WINDOW_clicked()
{
    line = 0;
}

void MainWindow::on_LINE_clicked()
{
    line = 1;
}

void MainWindow::on_clip_clicked()
{
    while(!l.empty()){
    tmp = l.top();
    l.pop();
    cohenSutherlandClip(tmp->x1,tmp->y1,tmp->x2,tmp->y2);
    }
    QImage AfterClip(300,300,QImage::Format_RGB888);
    while(!final.empty()){
        tmp = final.top();
        final.pop();
        dda(tmp->x1,tmp->y1,tmp->x2,tmp->y2,AfterClip);
    }
    image = AfterClip;
    ui -> label -> setPixmap(QPixmap:: fromImage(image));
    ui -> label -> show();
}
