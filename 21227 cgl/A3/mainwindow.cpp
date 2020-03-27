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
    dda(249,0,249,499,imageCross);
    dda(0,249,499,249,imageCross);
    mainImage = imageCross;
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
void dda(int x1, int y1, int x2,int y2,QImage &image){
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
Matrix points;
void drawNewPoints(Matrix &afterScale){
    //mainImage = clear;
    //mainImage = imageCross;
    cout<<"drawNewPoints"<<endl;
    for(int i = 0; i < afterScale.pointsCount - 1;i++){
        int xPrev = afterScale.mat[i][0];
        int yPrev = afterScale.mat[i][1];
        int x = afterScale.mat[i+1][0];
        int y = afterScale.mat[i+1][1];
        dda(xPrev,yPrev,x,y,mainImage);
    }
    int xPrev = afterScale.mat[afterScale.pointsCount - 1][0];
    int yPrev = afterScale.mat[afterScale.pointsCount - 1][1];
    int x = afterScale.mat[0][0];
    int y = afterScale.mat[0][1];
    dda(xPrev,yPrev,x,y,mainImage);
}
void MainWindow::mousePressEvent(QMouseEvent *m){
    //cout<<"mousePressEevnt"<<endl;
    if(m -> button() == Qt::RightButton){
        int x = points.mat[points.pointsCount-1][0];
        int y = points.mat[points.pointsCount-1][1];
        int xPrev = points.mat[0][0];
        int yPrev = points.mat[0][1];
        dda(x, y,xPrev,yPrev,mainImage);
    }
    else
    {
    if(points.pointsCount > 0){
        int x = points.mat[points.pointsCount][0] = m -> pos().x();
        int y = points.mat[points.pointsCount][1] = m -> pos().y();
        points.mat[points.pointsCount][2] = 1;
        int xPrev = points.mat[points.pointsCount - 1][0];
        int yPrev = points.mat[points.pointsCount - 1][1];
        //dda(0,0,50,50,mainImage);
        dda(x, y,xPrev,yPrev,mainImage);
    }
    else
    {
        points.mat[points.pointsCount][0] = m -> pos().x();
        points.mat[points.pointsCount][1] = m -> pos().y();
        points.mat[points.pointsCount][2] = 1;
    }
        points.pointsCount++;
    }

    ui->label->setPixmap(QPixmap::fromImage(mainImage));
    ui->label->show();
}

void MainWindow::on_pushButton_clicked()
{
    mainImage = clear;
    points.pointsCount = 0;
    mainImage = imageCross;
    ui->label->setPixmap(QPixmap::fromImage(mainImage));
    ui->label->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    //Tx = ui -> textEdit -> toPlainText().toFloat();
    //Ty = ui -> textEdit_2 -> toPlainText().toFloat();
    Sx = ui -> textEdit_3 -> toPlainText().toFloat();
    Sy = ui -> textEdit_4 -> toPlainText().toFloat();
    Tx = 249;
    Ty = 249;
    //cout<<"tx :"<<Tx<<endl;
    //cout<<"ty :"<<Ty<<endl;
    //cout<<"Sx :"<<Sx<<endl;
   //cout<<"Sy :"<<Sy<<endl;
    cout<<points.pointsCount<<endl;
    for(int i = 0; i< points.pointsCount; i++){
        cout<<points.mat[i][0]
            <<"\t"<<points.mat[i][1]
            <<"\t"<<points.mat[i][2]<<endl;
    }
    Matrix transform1(-Tx,-Ty,1,1);
    Matrix transform2(Tx,Ty,1,1);
    Matrix scale(0,0,Sx,Sy);
    scale = transform1 * scale;
    scale = scale * transform2;
    for(int i = 0; i< scale.pointsCount; i++){
        cout<<scale.mat[i][0]
            <<"\t"<<scale.mat[i][1]
            <<"\t"<<scale.mat[i][2]<<endl;
    }
    Matrix afterScale = points*scale;
    for(int i = 0; i< points.pointsCount; i++){
        cout<<afterScale.mat[i][0]
            <<"\t"<<afterScale.mat[i][1]
            <<"\t"<<afterScale.mat[i][2]<<endl;
    }
    drawNewPoints(afterScale);
    ui -> label -> setPixmap(QPixmap::fromImage(mainImage));
    ui -> label -> show();
}



void MainWindow::on_pushButton_3_clicked()
{
    // Translate Not Working
    Matrix afterTranslate;
    Tx = ui -> textEdit -> toPlainText().toFloat();
    Ty = ui -> textEdit_2 -> toPlainText().toFloat();
    Matrix translate(Tx,-Ty,1,1);
    afterTranslate = points * translate;
    for(int i = 0; i< points.pointsCount; i++){
        cout<<points.mat[i][0]
            <<"\t"<<points.mat[i][1]
            <<"\t"<<points.mat[i][2]<<endl;
    }
    drawNewPoints(afterTranslate);
    ui -> label -> setPixmap(QPixmap::fromImage(mainImage));
    ui -> label -> show();
}

void MainWindow::on_pushButton_4_clicked()
{
    float rotation = ui -> textEdit_5 -> toPlainText().toFloat();
    //rotation = (2 * 3.14) / 180;
    Matrix traslate1(-249,-249,1,1);
    Matrix traslate2(249,249,1,1);
    Matrix rot;
    rot.mat[0][0] = cos(rotation);
    rot.mat[0][1] = sin(rotation);
    rot.mat[1][0] = -sin(rotation);
    rot.mat[1][1] = cos(rotation);
    rot.mat[2][2] = 1;
    rot.pointsCount = 3;
    for(int i = 0; i< rot.pointsCount; i++){
        cout<<rot.mat[i][0]
            <<"\t"<<rot.mat[i][1]
            <<"\t"<<rot.mat[i][2]<<endl;
    }
    rot = traslate1 * rot;
    for(int i = 0; i< rot.pointsCount; i++){
        cout<<rot.mat[i][0]
            <<"\t"<<rot.mat[i][1]
            <<"\t"<<rot.mat[i][2]<<endl;
    }
    rot = rot * traslate2;
    for(int i = 0; i< rot.pointsCount; i++){
        cout<<rot.mat[i][0]
            <<"\t"<<rot.mat[i][1]
            <<"\t"<<rot.mat[i][2]<<endl;
    }
    Matrix afterRotation;
    afterRotation = points * rot;
    for(int i = 0; i< afterRotation.pointsCount; i++){
        cout<<afterRotation.mat[i][0]
            <<"\t"<<afterRotation.mat[i][1]
            <<"\t"<<afterRotation.mat[i][2]<<endl;
    }
    drawNewPoints(afterRotation);
    ui -> label -> setPixmap(QPixmap::fromImage(mainImage));
    ui -> label -> show();
}
