#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include <QDialog>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class KeyBoardDialog; }
QT_END_NAMESPACE

class KeyBoardDialog : public QDialog
{
    Q_OBJECT

public:
    KeyBoardDialog(QWidget *parent = nullptr);
    ~KeyBoardDialog();
    void keyPressEvent(QKeyEvent *);

private:
    Ui::KeyBoardDialog *ui;
};
#endif // KEYBOARDDIALOG_H
