#include "showimagedialog.h"
#include "ui_showimagedialog.h"

ShowImageDialog::ShowImageDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowImageDialog)
{
    ui->setupUi(this);
    m_index = 0;
}

ShowImageDialog::~ShowImageDialog()
{
    delete ui;
}


void ShowImageDialog::on_m_btn_prev_clicked()
{
    if(--m_index < 0){
        m_index = 9;
    }
    update();
}

void ShowImageDialog::on_m_btn_next_clicked()
{
    if(++m_index>9){
        m_index = 0;
    }
    update();
}

void ShowImageDialog::paintEvent(QPaintEvent*){
    //qDebug()<<"paintEvent";
    QPainter painter(this);
    QRect rect = ui->frame->frameRect();

    rect.translate(ui->frame->pos());
    qDebug()<<"平移后:"<<rect;
    QImage image(":/images/"+QString::number(m_index) + ".jpg");
    painter.drawImage(rect,image);

}
