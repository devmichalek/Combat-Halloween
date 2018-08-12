#ifndef LOGGINGWINDOW_H
#define LOGGINGWINDOW_H

#include <QMainWindow>

namespace Ui {
	class LoggingWindow;
}

class LoggingWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit LoggingWindow(QWidget *parent = 0);
	~LoggingWindow();

private:
	Ui::LoggingWindow *ui;
};

#endif // LOGGINGWINDOW_H