#include "videodisplayinqt.h"
#include "ui_videodisplayinqt.h"

videodisplayinqt::videodisplayinqt(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::videodisplayinqt)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(importFrame()));
}

videodisplayinqt::~videodisplayinqt()
{
    delete ui;
}


void videodisplayinqt::on_comboBox_currentIndexChanged(int index)
{
    index = ui->comboBox->currentIndex();
    if(index == 1)
        isCamera = 1;
    else
        isCamera = 0;
}

void videodisplayinqt::on_pushButton_clicked()
{
    if(isCamera)
       {
           capture.open(0);
       }
       else{
           capture.open("/home/chenbokai/桌面/upd_display/01.mp4");
       }

       timer->start(33);
}

void videodisplayinqt::on_pushButton_2_clicked()
{
    timer->stop();
    capture.release();
}

void videodisplayinqt::importFrame()
{
    capture >> frame;
    cvtColor(frame,frame,COLOR_BGR2RGB);
    QImage srcQImage = QImage((uchar*)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(srcQImage));
    ui->label->resize(srcQImage.size());
    ui->label->show();


}
