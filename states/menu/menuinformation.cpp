#include "menuinformation.h"
#include "user.h"
#include "loading.h"
#include "definitions.h"
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
	const char* path = cmm::JCANDLE_FONT_PATH;
	Loading::add(money.setFont(path));
	Loading::add(money_form.setFont(path));
	Loading::add(username.setFont(path));
	Loading::add(username_form.setFont(path));
	if (Loading::isError())	return;

	// Set text.
	money.setText("error");
	money_form.setText("Money: ");
	username.setText(cmm::User::getUsername());
	username_form.setText("Logged as ");

	// Set color.
	money.setFillColor(cmm::ERROR_COLOR);
	money_form.setFillColor(cmm::LOCKED_COLOR);
	username.setFillColor(cmm::SUCCESS_COLOR);
	username_form.setFillColor(cmm::LOCKED_COLOR);

	// Set size.
	float size = screen_h / TILE_HEIGHT;
	money.setSize(size);
	money_form.setSize(size);
	username.setSize(size);
	username_form.setSize(size);

	Loading::add(plank.load("images/other/title.png"));
	if (Loading::isError())	return;
	plank.setScale(screen_w / 2560, screen_h / 1440);
	plank.setPosition(screen_w / 3, 0);

	// Set position.
	username_form.setPosition(plank.getRight() -(username_form.getWidth() + username.getWidth() + screen_h / TILE_FULL_WIDTH), screen_h / 144);
	username.setPosition(username_form.getRight() + screen_h / 128, username_form.getTop());
	money_form.setPosition(username_form.getX(), username.getBot() + screen_h / 144);
	money.setPosition(money_form.getRight() + screen_w / 128, money_form.getY());

	Loading::add(scene.load("images/other/scene.png"));
	if (Loading::isError())	return;
	scene.setScale(screen_w / 2560, screen_h / 1440);
	scene.setPosition(screen_w / 9, screen_h - scene.getHeight());
	Loading::add(background.loadRepeated("images/other/sayagata.png", screen_w*1.5f, screen_h*1.5f, true));
	if (Loading::isError())	return;
	background.setScale(0.75, 0.75);
}

void MenuInformation::draw(sf::RenderWindow* &window)
{
	window->draw(background);
	window->draw(plank);
	window->draw(scene);
	window->draw(money);
	window->draw(money_form);
	window->draw(username);
	window->draw(username_form);
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
			money.setFillColor(cmm::LOADING_COLOR);
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
	request.setMessage("username=" + cmm::User::getUsername());
	request.setRequest("/combathalloween/getters/getmoney.php", sf::Http::Request::Post);
	request.setHttp("http://amichalek.pl/");

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
			money.setFillColor(cmm::SUCCESS_COLOR);
			thread.success = true;
		}
	}

	// Error
	if (!success)
	{
		money.setText("error");
		money.setFillColor(cmm::ERROR_COLOR);
	}

	// Set username and position again.
	username.setText(cmm::User::getUsername());
	username_form.setPosition(plank.getRight() - (username_form.getWidth() + username.getWidth() + screen_h / TILE_FULL_WIDTH), screen_h / 144);
	username.setPosition(username_form.getRight() + screen_h / 128, username_form.getTop());
	money_form.setPosition(username_form.getX(), username.getBot() + screen_h / 144);
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