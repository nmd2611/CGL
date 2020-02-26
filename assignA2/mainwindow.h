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
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void printCircle(int xc, int yc, int x, int y);

    void BresenhamCircle(int x,int y,int r);

    void BresenhamLine(int x1,int y1, int x2, int y2);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
