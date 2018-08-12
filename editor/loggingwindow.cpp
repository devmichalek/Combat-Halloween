#include "loggingwindow.h"
#include "ui_loggingwindow.h"
#include <qdesktopwidget.h>

LoggingWindow::LoggingWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoggingWindow)
{
	ui->setupUi(this);
	setMinimumSize(QDesktopWidget().availableGeometry(this).size() * 0.5);
	setMaximumSize(QDesktopWidget().availableGeometry(this).size() * 0.5);
	// setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setWindowIcon(QIcon("images/other/icon.png"));
	centralWidget()->setStyleSheet("background-image:url(\"images/other/tile.png\"); background-repeat: repeat-xy;");
	setWindowTitle("Combat Halloween Map Editor");
}

LoggingWindow::~LoggingWindow()
{
	delete ui;
}
