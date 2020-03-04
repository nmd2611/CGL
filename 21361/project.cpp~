#include "mainwindow.h"
#include <QApplication>
#include<QtGui>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QImage image(300, 300, QImage::Format_RGB888);
    QRgb value;      
    value=qRgb(0,255,0);   //set color of pixel as green
    image.setPixel(50,50,value);  //draws pixel with value
    image.setPixel(150,150,qRgb(255,255,255)); //draws pixel in white color at x,y      
    								//position.
    QLabel l;                              //shows pixel on screen
    l.setPixmap(QPixmap::fromImage(image));  
    l.show();
    
    return a.exec();

