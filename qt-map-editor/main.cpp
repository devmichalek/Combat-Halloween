#include "mainwindow.h"
#include <QApplication>
// #include <stdio.h>
#include <qpushbutton.h>

void handleButton(QPushButton &button)
{
    button.setText("chuj");
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QPushButton test;
    test.setText("TEST");
    test.setGeometry(0, 0, 50, 50);
    test.setParent(&w);
    QObject::connect(&test, SIGNAL(released()), &w, SLOT(handleButton(test)));

    w.show();
    return a.exec();
}
