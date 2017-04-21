#include "squigglewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SquiggleWindow w;
    w.show();

    return a.exec();
}
