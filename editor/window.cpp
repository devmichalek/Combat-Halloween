#include "window.h"
#include "ui_window.h"
#include <qdesktopwidget.h>

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
	ui->setupUi(this);
	setMinimumSize(QDesktopWidget().availableGeometry(this).size() * 0.85);
	setMaximumSize(QDesktopWidget().availableGeometry(this).size() * 0.85);
	// setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setWindowIcon(QIcon("images/other/icon.png"));
	centralWidget()->setStyleSheet("background-image:url(\"images/other/tile.png\"); background-repeat: repeat-xy;");
	setWindowTitle("Combat Halloween Map Editor");

	
	createActions();
	createMenus();
}

Window::~Window()
{
    delete ui;
}

void Window::createMenus()
{
	fileMenu = new QMenu;
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(uploadAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);
	// fileMenu->setParent(menubar);

	editMenu = new QMenu;
	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(undoAct);
	editMenu->addAction(redoAct);
	editMenu->addSeparator();
	editMenu->addAction(cutAct);
	editMenu->addAction(copyAct);
	editMenu->addAction(pasteAct);
	// editMenu->setParent(menubar);
}

void Window::createActions()
{
	// new file
	newAct = new QAction(tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New); // ctrl + n
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, &QAction::triggered, this, &Window::newFile);

	// open file
	openAct = new QAction(tr("&Open"), this);
	openAct->setShortcuts(QKeySequence::Open); // ctrl + o
	openAct->setStatusTip(tr("Open a file"));
	connect(openAct, &QAction::triggered, this, &Window::openFile);

	// save file
	saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save); // ctrl + s
	saveAct->setStatusTip(tr("Save a file"));
	connect(saveAct, &QAction::triggered, this, &Window::saveFile);

	// upload file
	uploadAct = new QAction(tr("&Upload"), this);
	uploadAct->setShortcuts(QKeySequence::Underline); // ctrl + u
	uploadAct->setStatusTip(tr("Upload a file"));
	connect(uploadAct, &QAction::triggered, this, &Window::uploadFile);

	// exit
	exitAct = new QAction(tr("&Close"), this);
	exitAct->setShortcuts(QKeySequence::Close); // ctrl + F4 / ctrl + w
	exitAct->setStatusTip(tr("Exit editor"));
	connect(exitAct, &QAction::triggered, this, &Window::exitFile);


	// undo
	undoAct = new QAction(tr("&Undo"), this);
	undoAct->setShortcuts(QKeySequence::Undo); // ctrl + z
	undoAct->setStatusTip(tr("Undo Action"));
	connect(undoAct, &QAction::triggered, this, &Window::undo);

	// redo
	redoAct = new QAction(tr("&Redo"), this);
	redoAct->setShortcuts(QKeySequence::Redo); // ctrl + shift + z
	redoAct->setStatusTip(tr("Redo"));
	connect(redoAct, &QAction::triggered, this, &Window::redo);

	// cut
	cutAct = new QAction(tr("&Cut"), this);
	cutAct->setShortcuts(QKeySequence::Cut); // ctrl + x
	cutAct->setStatusTip(tr("Cut"));
	connect(cutAct, &QAction::triggered, this, &Window::cut);

	// copy
	copyAct = new QAction(tr("&Copy"), this);
	copyAct->setShortcuts(QKeySequence::Copy); // ctrl + c
	copyAct->setStatusTip(tr("Copy"));
	connect(copyAct, &QAction::triggered, this, &Window::copy);

	// paste
	pasteAct = new QAction(tr("&Paste"), this);
	pasteAct->setShortcuts(QKeySequence::Paste); // ctrl + v
	pasteAct->setStatusTip(tr("Paste"));
	connect(pasteAct, &QAction::triggered, this, &Window::paste);
}




// Actions
void Window::newFile()
{

}

void Window::openFile()
{

}

void Window::saveFile()
{

}

void Window::uploadFile()
{

}

void Window::exitFile()
{

}



void Window::undo()
{

}

void Window::redo()
{

}

void Window::cut()
{

}

void Window::copy()
{

}

void Window::paste()
{

}
