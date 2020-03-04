#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>

QImage image(511, 351, QImage::Format_RGB888);

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


int MainWindow:: sign(float a)
{
    if(a<0)
        return -1;
    else if(a==0)
        return 0;
    else
        return 1;
}

QImage getI()
{
    return image;
}

void MainWindow::on_pushButton_clicked()
{
    float x1,y1,x2,y2;

    x1=ui->X1->toPlainText().toFloat();
    y1=ui->Y1->toPlainText().toFloat();
    x2=ui->X2->toPlainText().toFloat();
    y2=ui->Y2->toPlainText().toFloat();

    float l,del_y,del_x,temp1,temp2,x,y;

    QRgb value;

    temp1=x2-x1;
    temp2=y2-y1;

    if(abs(temp1)>=abs(temp2))
          l=abs(temp1);
    else
          l=abs(temp2);

    del_x=temp1/l;
    del_y=temp2/l;

    x=x1+0.5*sign(del_x);
    y=y1+0.5*sign(del_y);


    value=qRgb(255,255,255);
    for(int i=0;i<=l;i++)
    {
         image.setPixel(int(x),int(y),value);


         x=x+del_x;
         y=y+del_y;
    }

    ui->label_3->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_2_clicked()
{
    float x1,y1,x2,y2;

    x1=ui->X1->toPlainText().toFloat();
    y1=ui->Y1->toPlainText().toFloat();
    x2=ui->X2->toPlainText().toFloat();
    y2=ui->Y2->toPlainText().toFloat();

    float l,del_y,del_x,temp1,temp2,x,y;

    QRgb value;

    temp1=x2-x1;
    temp2=y2-y1;

    if(abs(temp1)>=abs(temp2))
          l=abs(temp1);
    else
          l=abs(temp2);

    del_x=temp1/l;
    del_y=temp2/l;

    x=x1+0.5*sign(del_x);
    y=y1+0.5*sign(del_y);


    value=qRgb(255,255,255);
    for(int i=0;i<=l;i++)
    {
        if(i%2==0)
                  image.setPixel(int(x)+10,int(y),value);
         x=x+del_x;
         y=y+del_y;
    }

    ui->label_3->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_3_clicked()
{

    float x1,y1,x2,y2;

    x1=ui->X1->toPlainText().toFloat();
    y1=ui->Y1->toPlainText().toFloat();
    x2=ui->X2->toPlainText().toFloat();
    y2=ui->Y2->toPlainText().toFloat();

    float l,del_y,del_x,temp1,temp2,x,y;

    QRgb value;

    temp1=x2-x1;
    temp2=y2-y1;

    if(abs(temp1)>=abs(temp2))
          l=abs(temp1);
    else
          l=abs(temp2);

    del_x=temp1/l;
    del_y=temp2/l;

    x=x1+0.5*sign(del_x);
    y=y1+0.5*sign(del_y);


    value=qRgb(255,255,255);
    for(int i=0;i<=l;i++)
    {
        if(i%7!=0 && i%7!=1)
                  image.setPixel(int(x)+20,int(y),value);

         x=x+del_x;
         y=y+del_y;
    }

    ui->label_3->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_4_clicked()
{
    float x1,y1,x2,y2;
    int mod1=12;
    int mod2=16;
    int cnt=0;

    x1=ui->X1->toPlainText().toFloat();
    y1=ui->Y1->toPlainText().toFloat();
    x2=ui->X2->toPlainText().toFloat();
    y2=ui->Y2->toPlainText().toFloat();

    float l,del_y,del_x,temp1,temp2,x,y;

    QRgb value;

    temp1=x2-x1;
    temp2=y2-y1;

    if(abs(temp1)>=abs(temp2))
          l=abs(temp1);
    else
          l=abs(temp2);

    del_x=temp1/l;
    del_y=temp2/l;

    x=x1+0.5*sign(del_x);
    y=y1+0.5*sign(del_y);


    value=qRgb(255,255,255);
    for(int i=0;i<=l;i++)
    {
        if(! ((cnt==mod1) || (cnt==mod1+1) || (cnt==mod1+2) )
            && !( (cnt==mod2) || (cnt==mod2+1) || (cnt==mod2+2) )   )
           {
                 image.setPixel(int(x)+30,int(y),value);
           }

         x=x+del_x;
         y=y+del_y;

         if(cnt==18)
                cnt=0;
         cnt++;
    }

    ui->label_3->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_5_clicked()
{

    float x1,y1,x2,y2;

    x1=ui->X1->toPlainText().toFloat();
    y1=ui->Y1->toPlainText().toFloat();
    x2=ui->X2->toPlainText().toFloat();
    y2=ui->Y2->toPlainText().toFloat();

    float l,del_y,del_x,temp1,temp2,x,y;

    QRgb value;

    temp1=x2-x1;
    temp2=y2-y1;

    if(abs(temp1)>=abs(temp2))
          l=abs(temp1);
    else
          l=abs(temp2);

    del_x=temp1/l;
    del_y=temp2/l;

    x=x1+0.5*sign(del_x);
    y=y1+0.5*sign(del_y);


    value=qRgb(255,255,255);
    for(int i=0;i<=l;i++)
    {
         image.setPixel(int(x)+40,int(y),value);
         image.setPixel(int(x+1)+40,int(y),value);
         image.setPixel(int(x+2)+40,int(y),value);
         image.setPixel(int(x+3)+40,int(y),value);

         x=x+del_x;
         y=y+del_y;
    }

    ui->label_3->setPixmap(QPixmap::fromImage(image));
}
