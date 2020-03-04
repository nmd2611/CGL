#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<qpainter.h>
#include<qpicture.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void drawBCircle(int x1,int y1,int r);
    void dda(int x1, int y1, int x2, int y2);
    void bresenham(int x1,int y1,int x2,int y2);

private:
    Ui::MainWindow *ui;
    QPicture pic;
    QPainter paint;
};

#endif // MAINWINDOW_H
