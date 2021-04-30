#include "timedialog.h"
#include "ui_timedialog.h"
#include <QFont>
TimeDialog::TimeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TimeDialog)
{
    ui->setupUi(this);
    m_label = new QLabel(this);
    m_label->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    m_label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    QFont font;
    font.setPointSize(20);
    m_label->setFont(font);

    m_button = new QPushButton("获取当前时间",this);
    m_button->setFont(font);

    //创建垂直布局器
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_label);
    layout->addWidget(m_button);

    setLayout(layout);

    connect(m_button,SIGNAL(clicked()),this,SLOT(getTime()));
}

TimeDialog::~TimeDialog()
{
    delete ui;
}

void TimeDialog::getTime(void)
{
    qDebug("get Time");
    qDebug()<<"get Time";

    QTime time = QTime::currentTime();
    QString str = time.toString("hh:mm:ss a");
    m_label->setText(str);

}
