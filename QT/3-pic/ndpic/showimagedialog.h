#ifndef SHOWIMAGEDIALOG_H
#define SHOWIMAGEDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QImage>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class ShowImageDialog; }
QT_END_NAMESPACE

class ShowImageDialog : public QDialog
{
    Q_OBJECT

public:
    ShowImageDialog(QWidget *parent = nullptr);
    ~ShowImageDialog();

private slots:
    void on_m_btn_prev_clicked();

    void on_m_btn_next_clicked();
private:
    void paintEvent(QPaintEvent*);

private:
    Ui::ShowImageDialog *ui;
    int m_index;
};
#endif // SHOWIMAGEDIALOG_H
