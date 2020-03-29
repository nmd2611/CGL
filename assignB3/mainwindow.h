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
    void on_pushButton_clicked();

    void DDALine(int x1,int y1, int x2, int y2,QRgb mycolor);

    void mousePressEvent(QMouseEvent *ev);

    void Cohen(int x1,int y1, int x2,int y2);
    int code(int x1,int y1);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int flag=0;
    int x[100],y[100];
    int i=0;




};
#endif // MAINWINDOW_H
