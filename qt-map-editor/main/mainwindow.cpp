#include "mainwindow.h"
#include <qdesktopwidget.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	setMinimumSize(QDesktopWidget().availableGeometry(this).size() * 0.85);
	setMaximumSize(QDesktopWidget().availableGeometry(this).size() * 0.85);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setWindowIcon(QIcon("images/other/icon.png"));
	this->centralWidget()->setStyleSheet("background-image:url(\"images/other/tile.png\"); background-repeat: repeat-xy;");
	this->setWindowTitle("Combat Halloween Map Editor");
}

MainWindow::~MainWindow()
{

}