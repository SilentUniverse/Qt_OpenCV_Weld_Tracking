#include "qcvwidget.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCvWidget w;
    w.show();
    return a.exec();
}
