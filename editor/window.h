#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
	Q_OBJECT
	QMenu* fileMenu;
	QMenu* editMenu;

	QAction* newAct;
	QAction* openAct;
	QAction* saveAct;
	QAction* uploadAct;
	QAction* exitAct;

	QAction *undoAct;
	QAction *redoAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

	void createMenus();
	void createActions();

private:
    Ui::Window *ui;

private slots:
	void newFile();
	void openFile();
	void saveFile();
	void uploadFile();
	void exitFile();

	void undo();
	void redo();
	void cut();
	void copy();
	void paste();
};

#endif // LOGGINGWINDOW_H