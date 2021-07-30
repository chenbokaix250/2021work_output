#include "videodisplayinqt.h"
#include "ui_videodisplayinqt.h"

videodisplayinqt::videodisplayinqt(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::videodisplayinqt)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    receiver = new QUdpSocket(this);
    receiver->bind(45454,QUdpSocket::ShareAddress);
    img_receiver = new QUdpSocket(this);
    img_receiver->bind(32323,QUdpSocket::ShareAddress);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
    connect(img_receiver,SIGNAL(readyRead()),this,SLOT(PicPendingDatagram()));
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

void videodisplayinqt::processPendingDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(),datagram.size());
        QString msg = datagram.data();

        ui->lab_test->setText(msg);
    }
}

void videodisplayinqt::on_pushButton_3_clicked()
{
    QString msg_save = ui->lab_test->text();
    QFile file("/home/chenbokai/user/upd_display/save.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(msg_save.toUtf8());
    file.close();
    qDebug()<<"txt保存成功！";
}

void videodisplayinqt::PicPendingDatagram()
{
    qDebug()<<"ok";
    QFile file("/home/chenbokai/user/upd_display/save.jpg");
    if(!file.open(QIODevice::WriteOnly)) return;
    file.resize(0);
    while(img_receiver->hasPendingDatagrams()){
        QByteArray datagram;

        datagram.resize(img_receiver->pendingDatagramSize());
        img_receiver->readDatagram(datagram.data(),datagram.size());
        if(datagram!="End!"){
            file.write(datagram.data(),datagram.size());
            qDebug()<<datagram.size()<<endl;

        }else{
            break;
        }
    }
    file.close();
    qDebug()<<"take over end!";

}
