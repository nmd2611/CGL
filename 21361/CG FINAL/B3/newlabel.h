#ifndef NEWLABEL_H
#define NEWLABEL_H

#include <QLabel>
#include<QMouseEvent>
class newLabel : public QLabel
{
    Q_OBJECT
public:
    int x1,y1;
    int x2,y2;
    bool firstPoint=true;
    int regionFirstPoint,regionSecondPoint;
    explicit newLabel(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);
signals:
    void FirstPoint();
    void SecondPoint();
public slots:
};
#endif // NEWLABEL_H
