#pragma once

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoginApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    secdialog.cpp

HEADERS  += mainwindow.h \
    secdialog.h

FORMS    += mainwindow.ui \
    secdialog.ui

RESOURCES += \
    resource.qrc