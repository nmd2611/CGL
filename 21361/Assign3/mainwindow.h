#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);
    void dda(int x1,int y1,int x2,int y2);
    void Flood_fill(int x,int y, QRgb fillcolor,QRgb bkcolor);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int a[10],b[10],x1,y1,x2,y2,ver;
    bool start;
};

#endif // MAINWINDOW_H
