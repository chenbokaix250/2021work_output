#include "videodisplayinqt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    videodisplayinqt w;
    w.show();
    return a.exec();
}
