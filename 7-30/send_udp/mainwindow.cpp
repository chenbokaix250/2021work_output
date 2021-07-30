#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QDebug>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QString msg = "[1,2,325243,324324,5,6.5466432,7.45346,8,9]";
    qDebug()<<msg;
    sender->writeDatagram(msg.toUtf8(),msg.length(),QHostAddress::LocalHost,45454);

}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("choose image"),".",tr("Images (*.jpg *.png)"));
    qDebug()<<fileName<<endl;
    if(fileName.isEmpty()){
        return;
    }

    QFile file;
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly)) return;
    while(!file.atEnd())
    {
        QByteArray line = file.read(8000);
        sender->writeDatagram(line, QHostAddress::LocalHost,32323);

    }
    QByteArray str = "End!";
    sender->writeDatagram(str.data(),str.size(),QHostAddress::LocalHost,32323);
    file.close();

}
