// Test of objects: loading, initialization, login, rectbutton
#include "core.h"
#include "loading.h"
#include "initialization.h"
#include "login.h"

enum STATES
{
	LOADING = 0,
	INIT,
	LOGIN,
	MENU,
};

Core* core = new Core(0, sf::Color(21, 21, 29, 0xFF));
Loading* loading = new Loading;
Initialization* initialization = nullptr;
Login* login = nullptr;

// Load function.
void load()
{
	loading->mechanics(core->getElapsedTime());
	loading->draw(core->getWindow());

	float screen_w = (float)core->getWidth();
	float screen_h = (float)core->getHeight();

	switch (loading->getState())
	{
	case 1:
		initialization = new Initialization;
		initialization->load(screen_w, screen_h);
		break;

	case 20:
		login = new Login;
		login->load(screen_w, screen_h);
		break;

	case 101:
		loading->beReady();
		break;
	}

	if (loading->isReady())
	{
		delete loading;
		loading = NULL;
		core->state = INIT;	// SET FIRST STATE.
	}
}

int main(int argc, char** argv)
{
	core->create("Combat Halloween");
	float screen_w = (float)core->getWidth();
	float screen_h = (float)core->getHeight();
	loading->load(screen_w, screen_h);
	while (core->open)
	{
		// clear
		core->clear();

		// events, mouse, keyboard
		while (core->isEvent())
		{
			if (core->getEvent().type == sf::Event::Closed)
			{
				core->open = false;
			}

			switch (core->state)
			{
			case LOGIN: login->handle(core->getEvent()); 	break;
			}
		}

		// states, displaying
		if (core->state == LOADING)
		{
			load();
		}

		if (core->state == INIT)
		{
			initialization->mechanics(core->getElapsedTime());
			initialization->draw(core->getWindow());

			if (initialization->isNext())
			{
				core->state = LOGIN;
				delete initialization;
				initialization = NULL;
			}
		}

		if (core->state == LOGIN)
		{
			login->mechanics(core->getElapsedTime());
			login->draw(core->getWindow());

			if (login->isNext())
			{
				core->state = MENU;
			}
		}

		if (core->state == MENU) {}

		// display
		core->display();
	}

	delete core;
	delete login;
	return 0;
}