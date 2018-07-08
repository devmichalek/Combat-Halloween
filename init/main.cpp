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

	switch (loading->getState())
	{
	case 1:
		initialization = new Initialization;
		initialization->load(core->getWidth(), core->getHeight());
		break;

	case 20:
		login = new Login;
		login->load(core->getWidth(), core->getHeight());
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
	loading->load(core->getWidth(), core->getHeight());
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