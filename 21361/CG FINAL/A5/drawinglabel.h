#ifndef DRAWINGLABEL_H
#define DRAWINGLABEL_H


#include <QLabel>
#include<QMouseEvent>
class drawingLabel : public QLabel
{
    Q_OBJECT
public:
    explicit drawingLabel(QWidget *parent = 0);
    int startX,startY;
    int X1,Y1;
    int X2,Y2;
    int x,y;
    int count=0;
    bool polygonComplete;
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void Mouse_Click();
    void Mouse_RecordStart();
    void Mouse_Hover();
    void Mouse_DClick();
public slots:
};

#endif // DRAWINGLABEL_H
