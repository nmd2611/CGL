#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<qpicture.h>
#include<qpainter.h>
#include<math.h>
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
    void displayBresenhmCircle(int xc_,int yc_, int x, int y);
    void breshnam(int xc_,int yc_,int radius_);

private:
    Ui::MainWindow *ui;
     QPicture pic;
     QPainter paint;
};

#endif // MAINWINDOW_H
