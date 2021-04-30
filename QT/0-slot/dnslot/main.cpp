#include "widget.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//widget w;
//w.show();

    QDialog parent;
    parent.resize(320,240);
    QLabel label("我是标签",&parent);
    label.move(50,40);
    QPushButton button("我是按钮",&parent);
    button.move(59,140);
    parent.show();
    QObject::connect(&button,SIGNAL(clicked()),&label,SLOT(close()));

    return a.exec();
}
