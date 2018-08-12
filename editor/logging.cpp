#include "logging.h"
#include <QtNetwork/QNetworkAccessManager.h>
#include <qmessagebox.h>
// #include <QTextStream>
#include <qdesktopwidget.h>

Logging::Logging()
{
	window = new Window;
	window->hide();
}

Logging::~Logging()
{
	layout.removeItem(&username_form);
	layout.removeItem(&password_form);
}

void Logging::load(QSize size)
{
	QFont font = this->font();
	font.setPointSize(size.height() / 20);
	setFont(font);
	setTitle("Sign In");
	setWindowIcon(QIcon("images/other/icon.png"));
	setGeometry(QRect(QPoint(size.width()/4, size.height()/4), QSize(size.width()/2, size.height()/2)));
	setAutoFillBackground(true);
	// setStyleSheet("font-size: 30px;");
	setLayout(&layout);
	

	user.setText("Username:");
	font = user.font();
	font.setPointSize(size.height() / 25);
	user.setFont(font);
	pass.setText("Password:");
	pass.setFont(font);

	userline.setEchoMode(QLineEdit::Normal);
	userline.setMaxLength(12);
	userline.setFont(font);
	connect(&userline, SIGNAL(returnPressed()), &passline, SLOT(setFocus()));
	passline.setEchoMode(QLineEdit::Password);
	passline.setMaxLength(20);
	passline.setFont(font);
	connect(&passline, SIGNAL(returnPressed()), &button, SLOT(setFocus()));

	username_form.addWidget(&user);
	username_form.addWidget(&userline);
	password_form.addWidget(&pass);
	password_form.addWidget(&passline);

	button.setText("Enter");
	button.setFont(font);
	button.setGeometry(QRect(QPoint(50, 50), QSize(size.width() / 4, size.height() / 4)));
	connect(&button, SIGNAL(clicked()), this, SLOT(sendRequest()));

	layout.addLayout(&username_form);
	layout.addLayout(&password_form);
	layout.addWidget(&button);
}

void Logging::setWindowAsParent(QWidget* widget)
{
	setParent(widget);
}

void Logging::sendRequest()
{
	QNetworkAccessManager * mgr = new QNetworkAccessManager(this);
	connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinishRequest(QNetworkReply*)));
	connect(mgr, SIGNAL(finished(QNetworkReply*)), mgr, SLOT(deleteLater()));

	QByteArray message;
	message.append("username=" + userline.text());
	message.append("&password=" + passline.text());

	mgr->post(QNetworkRequest(QUrl("http://amichalek.pl/combathalloween/getters/request.php/")), message);
}

void Logging::onFinishRequest(QNetworkReply* reply)
{
	QString result = "";
	QByteArray feedback = reply->readAll();

	if (feedback == "success")
	{
		result = QString("You are logged!");
		this->setVisible(false);
		parentWidget()->hide();
		window->show();
		QMessageBox::information(this, "Info", result, "Ok");
	}
	else
	{
		if (feedback == "-1")
			result = QString("Unexpected Error.");
		else if (feedback == "0")
			result = QString("Wrong username or password.");
		else
			result = QString("Cannot connect to database.");
		QMessageBox::warning(this, "Warning", result, "Ok");
	}	
}