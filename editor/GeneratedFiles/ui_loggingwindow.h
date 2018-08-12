/********************************************************************************
** Form generated from reading UI file 'loggingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGGINGWINDOW_H
#define UI_LOGGINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoggingWindow
{
public:
    QWidget *centralwidget;

    void setupUi(QMainWindow *LoggingWindow)
    {
        if (LoggingWindow->objectName().isEmpty())
            LoggingWindow->setObjectName(QStringLiteral("LoggingWindow"));

        centralwidget = new QWidget(LoggingWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        LoggingWindow->setCentralWidget(centralwidget);

        retranslateUi(LoggingWindow);
        QMetaObject::connectSlotsByName(LoggingWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoggingWindow)
    {
        LoggingWindow->setWindowTitle(QApplication::translate("LoggingWindow", "LoggingWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoggingWindow: public Ui_LoggingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGGINGWINDOW_H
