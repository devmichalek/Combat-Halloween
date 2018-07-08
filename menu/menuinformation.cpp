#include "menuinformation.h"
#include "state.h"
#include "boost/lexical_cast.hpp"
#include <ctime>

MenuInformation::MenuInformation()
{
	free();
}

MenuInformation::~MenuInformation()
{
	free();
}

void MenuInformation::free()
{
	screen_w = 0;
	screen_h = 0;
}



void MenuInformation::load(float screen_w, float screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	// Set font.
	const char* path = "fonts/jcandlestickextracond.ttf";
	money.setFont(path);
	money_form.setFont(path);
	username.setFont(path);
	username_form.setFont(path);

	// Set text.
	money.setText("error");
	money_form.setText("Money: ");
	username.setText(Username::getUsername());
	username_form.setText("Logged as ");

	// Set color.
	money.setFillColor(Username::getErrorColor());
	money_form.setFillColor(Username::getLockedColor());
	username.setFillColor(Username::getSuccessColor());
	username_form.setFillColor(Username::getLockedColor());

	// Set size.
	float size = screen_h / 32;
	money.setSize(size);
	money_form.setSize(size);
	username.setSize(size);
	username_form.setSize(size);

	plank.load("images/other/title.png");
	plank.setScale(screen_w / 2560, screen_h / 1440);
	plank.setPosition(screen_w / 3, 0);

	// Set position.
	username_form.setPosition(plank.getRight() -(username_form.getWidth() + username.getWidth() + screen_h / 64), screen_h / 144);
	username.setPosition(username_form.getRight() + screen_h / 128, username_form.getTop());
	money_form.setPosition(username_form.getX(), username.getBot() + screen_h / 144);
	money.setPosition(money_form.getRight() + screen_w / 128, money_form.getY());

	scene.load("images/other/scene.png");
	scene.setScale(screen_w / 2560, screen_h / 1440);
	scene.setPosition(screen_w / 9, screen_h - scene.getHeight());
	background.loadRepeated("images/other/sayagata.png", screen_w, screen_h, true);
}

void MenuInformation::draw(sf::RenderWindow* &window)
{
	window->draw(background.get());
	window->draw(plank.get());
	window->draw(scene.get());
	window->draw(money.get());
	window->draw(money_form.get());
	window->draw(username.get());
	window->draw(username_form.get());
}

void MenuInformation::mechanics()
{
	// Delete thread if is ready
	if (thread.ready)
	{
		thread.reset();
	}
}



void MenuInformation::fadein(float v, int max)
{
	money.fadein(v, max);
	money_form.fadein(v, max);
	username.fadein(v, max);
	username_form.fadein(v, max);

	plank.fadein(v, max);
	scene.fadein(v, max);
	background.fadein(v, max);
}

void MenuInformation::fadeout(float v, int min)
{
	money.fadeout(v, min);
	money_form.fadeout(v, min);
	username.fadeout(v, min);
	username_form.fadeout(v, min);

	plank.fadeout(v, min);
	scene.fadeout(v, min);
	background.fadeout(v, min);
}



void MenuInformation::setThread()
{
	if (!thread.success)
	{
		if (!thread.ready && !thread.thread)
		{
			// Money.
			money.setText("loading...");
			money.setFillColor(Username::getLoadingColor());
			money.setPosition(money_form.getRight() + screen_w / 128, money_form.getY());

			thread.thread = new std::thread(&MenuInformation::setMoney, this);
			thread.thread->detach();
		}
	}
}

void MenuInformation::reloadThread()
{
	thread.success = false;
}

void MenuInformation::setMoney()
{
	cmm::Request request;
	request.setMessage("username=" + boost::lexical_cast<std::string>(Username::getUsername()));
	request.setRequest("/combathalloween/getmoney.php", sf::Http::Request::Post);
	request.setHttp("http://adrianmichalek.pl/");

	bool success = request.sendRequest();
	if (success)
	{
		if (request.getResult() == "0")	// error
		{
			success = false;
		}
		else
		{
			money.setText(request.getResult());
			money.setFillColor(Username::getSuccessColor());
			thread.success = true;
		}
	}

	// Error
	if (!success)
	{
		money.setText("error");
		money.setFillColor(Username::getErrorColor());
	}

	money.setPosition(money_form.getRight() + screen_w / 128, money_form.getY());
	thread.ready = true;
}

bool MenuInformation::isReady() const
{
	return thread.success;
}

int MenuInformation::getBackgroundAlpha() const
{
	return static_cast <int> (background.getAlpha());
}