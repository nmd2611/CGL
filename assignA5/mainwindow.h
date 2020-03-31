#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void BresenhamLine(int x1,int y1, int x2, int y2);
    void FloodFill(float x, float y,QRgb q);

    void drawPolygon();
    void rotatePolygon();
    void fillPolygon();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void mousePressEvent(QMouseEvent *ev);

private:
    Ui::MainWindow *ui;
    float x[10][10];
    float y[10][10];
};
#endif // MAINWINDOW_H
