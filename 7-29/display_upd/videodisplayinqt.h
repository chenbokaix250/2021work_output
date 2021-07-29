#ifndef VIDEODISPLAYINQT_H
#define VIDEODISPLAYINQT_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTimer>

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

private:
    Ui::videodisplayinqt *ui;

    VideoCapture capture;
    QTimer *timer;
    Mat frame;
    bool isCamera = 0;
};
#endif // VIDEODISPLAYINQT_H
