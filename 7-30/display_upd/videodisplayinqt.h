#ifndef VIDEODISPLAYINQT_H
#define VIDEODISPLAYINQT_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QtNetwork>
using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class videodisplayinqt; }
QT_END_NAMESPACE

class videodisplayinqt : public QMainWindow
{
    Q_OBJECT

public:
    videodisplayinqt(QWidget *parent = nullptr);
    ~videodisplayinqt();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void importFrame();

    void processPendingDatagram();

    void on_pushButton_3_clicked();

    void PicPendingDatagram();

private:
    Ui::videodisplayinqt *ui;

    VideoCapture capture;
    QTimer *timer;
    Mat frame;
    bool isCamera = 0;
    QUdpSocket *receiver,*img_receiver;

};
#endif // VIDEODISPLAYINQT_H
