#include "widget.h"

#include <QApplication>
#include <QDialog>
#include <QSlider>
#include <QSpinBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDialog parent;
    parent.resize(320,240);

    QSlider slider(Qt::Horizontal,&parent);
    slider.move(20,100);
    QSpinBox spin(&parent);
    spin.move(220,100);

    QObject::connect(&slider,SIGNAL(valueChanged(int)),&spin,SLOT(setValue(int)));
    QObject::connect(&spin,SIGNAL(valueChanged(int)),&slider,SLOT(setValue(int)));
    parent.show();
    return a.exec();
}
