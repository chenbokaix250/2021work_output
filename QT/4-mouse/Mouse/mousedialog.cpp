#include "mousedialog.h"
#include "ui_mousedialog.h"

MouseDialog::MouseDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MouseDialog)
{
    ui->setupUi(this);
    m_drag = false;
}

MouseDialog::~MouseDialog()
{
    delete ui;
}


void MouseDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QRect rect = ui->label->frameRect();
        rect.translate(ui->label->pos());
        if(rect.contains(event->pos())){
            m_drag = true;
            m_pos = ui->label->pos() - event->pos();
        }

    }
}
void MouseDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_drag = false;
    }
}
void MouseDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(m_drag){
        QPoint newPos = event->pos() + m_pos;

        QSize s1 = size();
        QSize s2 = ui->label->size();

        if(newPos.x()<0){
            newPos.setX(0);
        }else if(newPos.x()>s1.width()-s2.width()){
            newPos.setX(s1.width()-s2.width());
        }
        if(newPos.y()<0){
            newPos.setY(0);
        }else if(newPos.y()>s1.height()-s2.height()){
            newPos.setY(s1.height()-s2.height());
        }

        ui->label->move(newPos);
        qDebug()<<newPos;

    }
}
