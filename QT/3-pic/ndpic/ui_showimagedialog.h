/********************************************************************************
** Form generated from reading UI file 'showimagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWIMAGEDIALOG_H
#define UI_SHOWIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ShowImageDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btn_prev;
    QPushButton *m_btn_next;

    void setupUi(QDialog *ShowImageDialog)
    {
        if (ShowImageDialog->objectName().isEmpty())
            ShowImageDialog->setObjectName(QString::fromUtf8("ShowImageDialog"));
        ShowImageDialog->resize(800, 600);
        verticalLayout = new QVBoxLayout(ShowImageDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(ShowImageDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btn_prev = new QPushButton(ShowImageDialog);
        m_btn_prev->setObjectName(QString::fromUtf8("m_btn_prev"));

        horizontalLayout->addWidget(m_btn_prev);

        m_btn_next = new QPushButton(ShowImageDialog);
        m_btn_next->setObjectName(QString::fromUtf8("m_btn_next"));

        horizontalLayout->addWidget(m_btn_next);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ShowImageDialog);

        QMetaObject::connectSlotsByName(ShowImageDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowImageDialog)
    {
        ShowImageDialog->setWindowTitle(QCoreApplication::translate("ShowImageDialog", "showpic", nullptr));
        m_btn_prev->setText(QCoreApplication::translate("ShowImageDialog", "\344\270\212\344\270\200\345\274\240", nullptr));
        m_btn_next->setText(QCoreApplication::translate("ShowImageDialog", "\344\270\213\344\270\200\345\274\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowImageDialog: public Ui_ShowImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWIMAGEDIALOG_H
