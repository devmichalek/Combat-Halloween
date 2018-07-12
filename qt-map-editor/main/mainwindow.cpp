#include "mainwindow.h"
#include <qdesktopwidget.h>

mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setMinimumSize(QDesktopWidget().availableGeometry(this).size() * 0.75);
	setMaximumSize(QDesktopWidget().availableGeometry(this).size() * 0.85);
	statusBar()->setSizeGripEnabled(true);
	setWindowIcon(QIcon("images/other/icon.png"));
}
