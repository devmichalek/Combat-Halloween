#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <qmenubar.h>

class MainWindow : public QMainWindow
{
	Q_OBJECT
	Ui::mainwindowClass ui;

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
};
