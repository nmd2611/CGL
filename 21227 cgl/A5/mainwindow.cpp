#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMouseEvent>
#include <algorithm>
#include <bits/stdc++.h>
#include <QStack>
#include <iostream>
#include <QVector>
using namespace std;
float arrx[50] = {0};
float arry[50] = {0};
QRgb value = qRgb(0,255,0);
QImage mainImage(500,500,QImage::Format_RGB888);
QImage imageCross(500,500,QImage::Format_RGB888);
QImage imageFinal(500,500,QImage::Format_RGB888);
QImage clear(500,500,QImage::Format_RGB888);
float Tx= 0 ,Ty = 0, Sx = 0,Sy = 0;
class Matrix;
void dda(int x1, int y1, int x2,int y2,QImage &image);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(mainImage));
    ui->label->show();
}
class Matrix{
public:
    float mat[50][3] = {0};
    int pointsCount = 0;
    Matrix(){

    }
    Matrix(float Tx, float Ty, float Sx, float Sy){
        pointsCount = 3;
        mat[0][0] = Sx;
        mat[1][1] = Sy;
        mat[2][0] = Tx;
        mat[2][1] = Ty;
        mat[2][2] = 1;
    }
    Matrix operator *(Matrix &tmp);
};
Matrix Matrix :: operator *(Matrix &afterScale){
    Matrix tmp;
    for(int i = 0; i < pointsCount;i++){
        for(int j = 0; j < 3; j++){
            float sum = 0;
            for(int k = 0; k< 3;k++){
                sum = sum + mat[i][k] * afterScale.mat[k][j];
            }
            tmp.mat[i][j] = sum;
        }
    }
    tmp.pointsCount = pointsCount;
    return tmp;
}
MainWindow::~MainWindow()
{
    delete ui;
}
void floodrec(int x, int y)
{
    if(mainImage.pixelColor(x,y) == qRgb(0,0,0))
    {
        mainImage.setPixel(x,y,value);
        floodrec(x+1,y);
        floodrec(x,y+1);
        floodrec(x-1,y);
        floodrec(x,y-1);
    }
}
void dda(float x1, float y1, float x2,float y2,QImage &image){
    float length = 0;
    if(abs(x2-x1) >= abs(y2-y1))
        length = abs(x2 - x1);
    else
        length = abs(y2 - y1);

    float delta_x = (x2 - x1)/length;
    float delta_y = (y2 - y1)/length;
    float x = x1 + 0.5;
    float y = y1 + 0.5;
    for(int i = 0; i < length; i++){
        image.setPixel(int(x),int(y), value);
        x += delta_x;
        y += delta_y;
    }
}
Matrix points[7];
Matrix colorCenter;
const int segmentCount = 7;
void drawNewPoints(Matrix* afterScale){
     mainImage = clear;
    cout<<"drawNewPoints"<<endl;
    for(int j = 0;  j < 7; j++)
    for(int i = 0; i < afterScale[j].pointsCount - 1;i++){
        float xPrev = afterScale[j].mat[i][0];
        float yPrev = afterScale[j].mat[i][1];
        float x = afterScale[j].mat[i+1][0];
        float y = afterScale[j].mat[i+1][1];
        dda(xPrev,yPrev,x,y,mainImage);
    }
}
int p = 0;

/*
void MainWindow::on_pushButton_clicked()
{
        mainImage = clear;
        points[1].pointsCount = 0;
        mainImage = imageCross;
        ui->label->setPixmap(QPixmap::fromImage(mainImage));
        ui->label->show();
}
*/
/*void MainWindow::on_pushButton_2_clicked()
{
    float rotation = ui -> textEdit_5 -> toPlainText().toFloat();
    //rotation = (2 * 3.14) / 180;

    drawNewPoints(afterRotation);
    ui -> label -> setPixmap(QPixmap::fromImage(mainImage));
    ui -> label -> show();
}
*/

void MainWindow::on_pushButton_clicked()
{
    p++;
    float x1 = 100, y1 = 100;
    float x2 = 400, y2 = 400;
    points[0].mat[0][0] = x1;
    points[0].mat[0][1] = y1;
    points[0].mat[0][2] = 1;
    points[0].mat[1][0] = x1;
    points[0].mat[1][1] = y2;
    points[0].mat[1][2] = 1;
    points[0].mat[2][0] = x2;
    points[0].mat[2][1] = y2;
    points[0].mat[2][2] = 1;
    points[0].mat[3][0] = x2;
    points[0].mat[3][1] = y1;
    points[0].mat[3][2] = 1;
    points[0].mat[4][0] = x1;
    points[0].mat[4][1] = y1;
    points[0].mat[4][2] = 1;
    points[0].pointsCount = 5;
    points[1].mat[0][0] =  (x1);
    points[1].mat[0][1] = abs((3 * y2) + y1)/4;
    points[1].mat[0][2] = 1;
    points[1].mat[1][0] =  (x2);
    points[1].mat[1][1] = abs((3 * y2) + y1)/4;
    points[1].mat[1][2] = 1;
    points[1].pointsCount = 2;
    points[2].mat[0][0] =  (x1);
    points[2].mat[0][1] = abs((1 * y2) + 3 *y1)/4;
    points[2].mat[0][2] = 1;
    points[2].mat[1][0] =  (x2);
    points[2].mat[1][1] = abs((1 * y2) + 3 * y1)/4;
    points[2].mat[1][2] = 1;
    points[2].pointsCount = 2;
    points[3].mat[0][0] =  (x1);
    points[3].mat[0][1] = abs((2 * y2) + 2 * y1)/4;
    points[3].mat[0][2] = 1;
    points[3].mat[1][0] =  (x2);
    points[3].mat[1][1] = abs((2 * y2) + 2 * y1)/4;
    points[3].mat[1][2] = 1;
    points[3].pointsCount = 2;
    //
    points[4].mat[0][0] =  abs((3 * x2) + 1 * x1)/4;
    points[4].mat[0][1] = y1;
    points[4].mat[0][2] = 1;
    points[4].mat[1][0] =  abs((3 * x2) + 1 * x1)/4;
    points[4].mat[1][1] = y2;
    points[4].mat[1][2] = 1;
    points[4].pointsCount = 2;
    points[5].mat[0][0] =  abs((2 * x2) + 2 * x1)/4;
    points[5].mat[0][1] = y1;
    points[5].mat[0][2] = 1;
    points[5].mat[1][0] =  abs((2 * x2) + 2 * x1)/4;
    points[5].mat[1][1] = y2;
    points[5].mat[1][2] = 1;
    points[5].pointsCount = 2;
    points[6].mat[0][0] =  abs((1 * x2) +  3* x1)/4;
    points[6].mat[0][1] = y1;
    points[6].mat[0][2] = 1;
    points[6].mat[1][0] =  abs((1 * x2) + 3 * x1)/4;
    points[6].mat[1][1] = y2;
    points[6].mat[1][2] = 1;
    points[6].pointsCount = 2;
    //centers
    colorCenter.mat[0][0] = (1 * x2 + 7 * x1)/8;
    colorCenter.mat[0][1] = ((3 * y2 + 5 * y1)/8);
    colorCenter.mat[0][2] = 1;
    colorCenter.mat[1][0] = (1 * x2 + 7 * x1)/8;
    colorCenter.mat[1][1] = ((7 * y2 + 1 * y1)/8);
    colorCenter.mat[1][2] = 1;
    colorCenter.mat[2][0] = (3 * x2 + 5 * x1)/8;
    colorCenter.mat[2][1] = ((1 * y2 + 7 * y1)/8);
    colorCenter.mat[2][2] = 1;
    colorCenter.mat[3][0] = (3 * x2 + 5 * x1)/8;
    colorCenter.mat[3][1] = ((5 * y2 + 3 * y1)/8);
    colorCenter.mat[3][2] = 1;
    colorCenter.mat[4][0] = (5 * x2 + 3 * x1)/8;
    colorCenter.mat[4][1] = ((3 * y2 + 5 * y1)/8);
    colorCenter.mat[4][2] = 1;
    colorCenter.mat[5][0] = (5 *x2+ 3 * x1)/8;
    colorCenter.mat[5][1] = ((7 * y2 + 1 * y1)/8);
    colorCenter.mat[5][2] = 1;
    colorCenter.mat[6][0] = (7 * x2 + 1 * x1)/8;
    colorCenter.mat[6][1] = ((1 * y2 + 7 * y1)/8);
    colorCenter.mat[6][2] = 1;
    colorCenter.mat[7][0] = (7 * x2 + 1 * x1)/8;
    colorCenter.mat[7][1] = ((5 * y2 + 3 * y1)/8);
    colorCenter.mat[7][2] = 1;
    colorCenter.pointsCount = 8;
    cout<<points[0].mat[0][0]<<"\t"<<points[0].mat[0][1]<<endl;
    cout<<(int)colorCenter.mat[0][0]<<endl;
    cout<<(int)colorCenter.mat[0][1]<<endl;
    drawNewPoints(points);

    //mainImage.setPixel((int)colorCenter.mat[0][0], (int)colorCenter.mat[0][1],value);
    //mainImage.setPixel((int)colorCenter.mat[1][0], (int)colorCenter.mat[1][1],value);
    //mainImage.setPixel((int)colorCenter.mat[2][0],(int) (int)colorCenter.mat[2][1],value);
    //mainImage.setPixel((int)colorCenter.mat[3][0], (int)colorCenter.mat[3][1],value);
    //mainImage.setPixel((int)colorCenter.mat[4][0], (int)colorCenter.mat[4][1],value);
    //mainImage.setPixel((int)colorCenter.mat[5][0], (int)colorCenter.mat[5][1],value);
   //mainImage.setPixel((int)colorCenter.mat[6][0], (int)colorCenter.mat[6][1],value);
   // mainImage.setPixel((int)colorCenter.mat[7][0],(int) colorCenter.mat[7][1],value);
    ui->label->setPixmap(QPixmap::fromImage(mainImage));
    ui->label->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    float rotation = 45;
    Matrix traslate1(-249,-249,1,1);
    Matrix traslate2(249,249,1,1);
    Matrix rot;
    rot.mat[0][0] = 0.70710678118;
    rot.mat[0][1] = 0.70710678118;
    rot.mat[1][0] = -0.70710678118;
    rot.mat[1][1] = 0.70710678118;
    rot.mat[2][2] = 1;
    rot.pointsCount = 3;
    rot = traslate1 * rot;
    rot = rot * traslate2;
    for(int i =0; i < 7 ; i++){
        points[i] = points[i] * rot;
    }
    colorCenter = colorCenter * rot;
    drawNewPoints(points);
    ui->label->setPixmap(QPixmap::fromImage(mainImage));
    ui->label->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    drawNewPoints(points);
    floodrec(colorCenter.mat[0][0], colorCenter.mat[0][1]);
    floodrec(colorCenter.mat[1][0], colorCenter.mat[1][1]);
    floodrec(colorCenter.mat[2][0], colorCenter.mat[2][1]);
    floodrec(colorCenter.mat[3][0], colorCenter.mat[3][1]);
    floodrec(colorCenter.mat[4][0], colorCenter.mat[4][1]);
    floodrec(colorCenter.mat[5][0], colorCenter.mat[5][1]);
    floodrec(colorCenter.mat[6][0], colorCenter.mat[6][1]);
    floodrec(colorCenter.mat[7][0], colorCenter.mat[7][1]);
    ui->label->setPixmap(QPixmap::fromImage(mainImage));
    ui->label->show();
}
