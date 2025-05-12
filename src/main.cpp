#include "../include/Widgets/SceneViewport.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SceneViewport w;
    w.show();
    return a.exec();
}
