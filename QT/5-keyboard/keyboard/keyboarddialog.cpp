#include "keyboarddialog.h"
#include "ui_keyboarddialog.h"

KeyBoardDialog::KeyBoardDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::KeyBoardDialog)
{
    ui->setupUi(this);
}

KeyBoardDialog::~KeyBoardDialog()
{
    delete ui;
}

void KeyBoardDialog::keyPressEvent(QKeyEvent *event){
    int x = ui->label->pos().x();
    int y = ui->label->pos().y();
    if(event->key() == Qt::Key_Up){
        ui->label->move(x,y-10);
    }else if(event->key() == Qt::Key_Down){
        ui->label->move(x,y+10);
    }else if(event->key() == Qt::Key_Left){
        ui->label->move(x-10,y);
    }else if(event->key() == Qt::Key_Right){
        ui->label->move(x+10,y);
    }

}
