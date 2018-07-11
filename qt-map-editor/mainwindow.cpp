#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdesktopwidget.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Added by me
    setMinimumSize(QDesktopWidget().availableGeometry(this).size() * 0.75);
    setMaximumSize(QDesktopWidget().availableGeometry(this).size() * 0.85);
    statusBar()->setSizeGripEnabled(true);
    setWindowIcon(QIcon("C:/Users/adriqun/Documents/Qt Projects/CombatHalloweenMapEditor/icon.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
