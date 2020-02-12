/********************************************************************************
** Form generated from reading UI file 'ChattingClient.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATTINGCLIENT_H
#define UI_CHATTINGCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChattingClientClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChattingClientClass)
    {
        if (ChattingClientClass->objectName().isEmpty())
            ChattingClientClass->setObjectName(QString::fromUtf8("ChattingClientClass"));
        ChattingClientClass->resize(600, 400);
        menuBar = new QMenuBar(ChattingClientClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ChattingClientClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChattingClientClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ChattingClientClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ChattingClientClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ChattingClientClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChattingClientClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ChattingClientClass->setStatusBar(statusBar);

        retranslateUi(ChattingClientClass);

        QMetaObject::connectSlotsByName(ChattingClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChattingClientClass)
    {
        ChattingClientClass->setWindowTitle(QCoreApplication::translate("ChattingClientClass", "ChattingClient", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChattingClientClass: public Ui_ChattingClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATTINGCLIENT_H
