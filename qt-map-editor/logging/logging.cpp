#include "logging.h"

NetworkManager::NetworkManager()
{

}

NetworkManager::~NetworkManager()
{

}

void NetworkManager::setUrl(QString host)
{
	url.setHost(host);
}

void NetworkManager::addQuery(QString s1, QString s2)
{
	
}



Logging::Logging()
{

}

Logging::~Logging()
{
	layout.removeItem(&username_form);
	layout.removeItem(&password_form);
}

void Logging::load(QSize size)
{
	setTitle("Log In");
	setWindowIcon(QIcon("images/other/icon.png"));
	setGeometry(QRect(QPoint(size.width()/4, size.height()/4), QSize(size.width()/2, size.height()/2)));
	setAutoFillBackground(true);
	setStyleSheet("font-size: 30px;");
	setLayout(&layout);

	user.setText("Username:");
	pass.setText("Password:");

	userline.setEchoMode(QLineEdit::Normal);
	passline.setEchoMode(QLineEdit::Password);

	username_form.addWidget(&user);
	username_form.addWidget(&userline);
	password_form.addWidget(&pass);
	password_form.addWidget(&passline);

	button.setText("Enter");
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
	setVisible(false);
}