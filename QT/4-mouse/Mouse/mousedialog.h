#ifndef MOUSEDIALOG_H
#define MOUSEDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QtDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MouseDialog; }
QT_END_NAMESPACE

class MouseDialog : public QDialog
{
    Q_OBJECT

public:
    MouseDialog(QWidget *parent = nullptr);
    ~MouseDialog();
private:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    Ui::MouseDialog *ui;
    bool m_drag;
    QPoint m_pos;
};
#endif // MOUSEDIALOG_H
