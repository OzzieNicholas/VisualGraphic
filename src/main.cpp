#include "../include/Basic/BasicAxis.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BasicAxis w;
    w.show();
    return a.exec();
}
