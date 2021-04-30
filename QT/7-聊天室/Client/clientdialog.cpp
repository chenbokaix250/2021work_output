#include "clientdialog.h"
#include "ui_clientdialog.h"

ClientDialog::ClientDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClientDialog)
{
    ui->setupUi(this);
    status = false;//离线状态
    connect(&tcpSocket,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(&tcpSocket,SIGNAL(disconnected()),this,SLOT(onDisconnected()));
    connect(&tcpSocket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(&tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onError()));
}

ClientDialog::~ClientDialog()
{
    delete ui;
}


void ClientDialog::on_sendButton_clicked()
{
    //获取用户输入聊天消息
    QString msg = ui->messageEdit->text();
    if(msg==""){
        return;
    }
    msg = username + ":" + msg;
    tcpSocket.write(msg.toUtf8());
    //清空消息输入框
    ui->messageEdit->clear();
}

void ClientDialog::on_connectButton_clicked()
{
    //如果当前是离线状态,则建立和服务器连接
    if(status == false){
        //获取服务器IP
        serverIP.setAddress(ui->serverIPEdit->text());
        //获取服务器的端口
        serverPort = ui->serverPortEdot->text().toShort();
        //获取聊天室的昵称
        username = ui->usernameEdit->text();
        //向服务器发送连接请求
        //成功 connected
        //失败 error
        tcpSocket.connectToHost(serverIP,serverPort);
    }
    //如果是在线状态,则断开和服务器连接
    else{
        //向服务器发送离开聊天室的提示消息
        QString msg = username + "离开了聊天室!";
        tcpSocket.write(msg.toUtf8());
        //关闭和服务器连接,同时发送信号
        tcpSocket.disconnectFromHost();
    }
}

//和服务器连接成功时执行的槽函数
void ClientDialog::onConnected(){
    status = true;//在线
    ui->sendButton->setEnabled(true);
    ui->serverIPEdit->setEnabled(false);
    ui->serverPortEdot->setEnabled(false);
    ui->usernameEdit->setEnabled(false);
    ui->connectButton->setText("离开聊天室");

    //想服务器发送进入聊天室提示消息
    QString msg = username + "进入了聊天室";
    //toUtf8:QString转换QByteArray
    tcpSocket.write(msg.toUtf8());
}
//和服务器断开连接时执行的槽函数
void ClientDialog::onDisconnected(){

    status = false;//在线
    ui->sendButton->setEnabled(false);
    ui->serverIPEdit->setEnabled(true);
    ui->serverPortEdot->setEnabled(true);
    ui->usernameEdit->setEnabled(true);
    ui->connectButton->setText("连接");
}
//接收聊天消息的槽函数
void ClientDialog::onReadyRead(){

    if(tcpSocket.bytesAvailable()){
        QByteArray buf = tcpSocket.readAll();

        //显示消息
        ui->listWidget->addItem(buf);
        ui->listWidget->scrollToBottom();
    }
}
//网络异常执行的槽函数
void ClientDialog::onError(){
    //获取网络异常的原因
    QMessageBox::critical(this,"ERROR",tcpSocket.errorString());
}
