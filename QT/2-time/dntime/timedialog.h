#ifndef TIMEDIALOG_H
#define TIMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTime>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class TimeDialog; }
QT_END_NAMESPACE

class TimeDialog : public QDialog
{
    Q_OBJECT

public:
    TimeDialog(QWidget *parent = nullptr);
    ~TimeDialog();
public slots:
    void getTime(void);
private:
    Ui::TimeDialog *ui;
    QLabel* m_label;
    QPushButton* m_button;
};
#endif // TIMEDIALOG_H
