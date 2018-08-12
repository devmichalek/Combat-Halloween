#pragma once
#include <qgroupbox.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qstring.h>
#include <qnetworkreply.h>
#include "window.h"

class Logging :public QGroupBox
{
	Q_OBJECT
	QLabel user, pass;
	QLineEdit userline, passline;
	QHBoxLayout username_form;
	QHBoxLayout password_form;
	QPushButton button;
	QVBoxLayout layout;
	Window* window;

public:
	Logging();
	~Logging();

	void load(QSize size);
	void setWindowAsParent(QWidget* widget);
private slots:
	void sendRequest();
	void onFinishRequest(QNetworkReply* reply);
};