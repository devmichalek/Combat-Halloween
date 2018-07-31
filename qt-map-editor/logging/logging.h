#pragma once
#include <qgroupbox.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QtNetwork/QNetworkAccessManager.h>
#include <qstring.h>

class NetworkManager :public QNetworkAccessManager
{
	QUrl url;
	QNetworkRequest request;
	QUrl parameters;
public:
	NetworkManager();
	~NetworkManager();

	void setUrl(QString host);
	void addQuery(QString s1, QString s2);
};

class Logging :public QGroupBox
{
	Q_OBJECT
	QLabel user, pass;
	QLineEdit userline, passline;
	QHBoxLayout username_form;
	QHBoxLayout password_form;
	QPushButton button;
	QVBoxLayout layout;
	NetworkManager network;

public:
	Logging();
	~Logging();

	void load(QSize size);
	void setWindowAsParent(QWidget* widget);

public slots:
	void sendRequest();
};