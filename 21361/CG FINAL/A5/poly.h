#ifndef POLY_H
#define POLY_H
#include <QMainWindow>
#include"drawinglabel.h"
#include<QStack>
namespace Ui {
class Poly;
}

class Poly : public QMainWindow
{
    Q_OBJECT

public:
    QImage image;
    QRgb fillColor;
    drawingLabel *nl;
    void seedFill();
    void draw_line(int x1,int y1,int x2,int y2,int red,int green,int blue);
    int sign(int);
    void mousePressed();
    void showFirstPoint();
    void mouseHover();
    QStack<int> s;
    explicit Poly(QWidget *parent = 0);
    ~Poly();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Poly *ui;
};

#endif // POLY_H
