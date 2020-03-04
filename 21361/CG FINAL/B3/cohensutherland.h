#ifndef COHENSUTHERLAND_H
#define COHENSUTHERLAND_H

#include <QMainWindow>
#include<math.h>
#include"newlabel.h"
namespace Ui {
class CohenSutherland;
}

class CohenSutherland : public QMainWindow
{
    Q_OBJECT

public:
    newLabel *nl;
    QImage image;
    int Xmin,Ymin;
    int Xmax,Ymax;
    void draw_line(int,int,int,int,int,int,int);
    int sign(int);
    void firstPointHandler();
    void secondPointHandler();
    void CohenSutherlandLineClipping();
    short int decideRegion(int,int);
    explicit CohenSutherland(QWidget *parent = 0);
    ~CohenSutherland();

private:
    Ui::CohenSutherland *ui;
};

#endif // COHENSUTHERLAND_H
