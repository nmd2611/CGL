#include "transformations.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Transformations w;
    w.show();
    
    return a.exec();
}
