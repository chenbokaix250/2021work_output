/********************************************************************************
** Form generated from reading UI file 'serverdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERDIALOG_H
#define UI_SERVERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ServerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *portEdit;
    QPushButton *createButton;

    void setupUi(QDialog *ServerDialog)
    {
        if (ServerDialog->objectName().isEmpty())
            ServerDialog->setObjectName(QString::fromUtf8("ServerDialog"));
        ServerDialog->resize(290, 456);
        verticalLayout = new QVBoxLayout(ServerDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(ServerDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ServerDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        portEdit = new QLineEdit(ServerDialog);
        portEdit->setObjectName(QString::fromUtf8("portEdit"));

        horizontalLayout->addWidget(portEdit);


        verticalLayout->addLayout(horizontalLayout);

        createButton = new QPushButton(ServerDialog);
        createButton->setObjectName(QString::fromUtf8("createButton"));

        verticalLayout->addWidget(createButton);


        retranslateUi(ServerDialog);

        QMetaObject::connectSlotsByName(ServerDialog);
    } // setupUi

    void retranslateUi(QDialog *ServerDialog)
    {
        ServerDialog->setWindowTitle(QCoreApplication::translate("ServerDialog", "\350\201\212\345\244\251\345\256\244\346\234\215\345\212\241\345\231\250", nullptr));
        label->setText(QCoreApplication::translate("ServerDialog", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243:", nullptr));
        portEdit->setText(QCoreApplication::translate("ServerDialog", "8080", nullptr));
        createButton->setText(QCoreApplication::translate("ServerDialog", "\345\210\233\345\273\272\346\234\215\345\212\241\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerDialog: public Ui_ServerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERDIALOG_H
