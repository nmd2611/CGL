#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include<qpainter.h>
#include<qpicture.h>
#include <QMainWindow>

namespace Ui {
class Transformations;
}

class Transformations : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Transformations(QWidget *parent = 0);
    ~Transformations();
    
private slots:
    void on_pushButton_2_clicked();
void dda(int x1,int y1,int x2,int y2);
void draw();
    void on_pushButton_clicked();

    void on_translation_clicked();

    void on_scaling_clicked();

    void on_rotation_clicked();

private:
    Ui::Transformations *ui;
    QPicture pic;
    QPainter paint;
};

#endif // TRANSFORMATIONS_H
