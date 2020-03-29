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
    void HilbertCurve(int u,int r,int d, int l, int h,int i,int& x,int& y);
    void move(int j,int h,int& x,int& y);
    void DDALine(int x1,int y1, int x2, int y2);

    void on_label_2_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
