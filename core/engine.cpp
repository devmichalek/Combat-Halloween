#include "engine.h"
#include <stdio.h>
#include <cstdlib>

Engine::Engine(int initState, int endState)
{
	// Set init state.
	this->initState = initState;
	this->endState = endState;

	// Set seed.
	srand(static_cast<int>(time(NULL)));

	// Set core.
	core = std::make_unique<Core>(STATES::LOADING, 21, 21, 29, 0xFF);
	core->create("Combat Halloween");
	core->setIcon("images/other/icon.png");

	// Set loading.
	loading = new Loading;
	loading->load(core->getWidth(), core->getHeight());
}

void Engine::loop()
{
	while (core->open)
	{
		events();
		core->clear();
		states();
		core->display();
	}
}

void Engine::load()
{
	loading->mechanics(core->getElapsedTime());
	loading->draw(core->getWindow());

	switch (loading->getState())
	{
	case 1:
		if (INIT >= initState && INIT <= endState)
		{
			initialization = new Initialization;
			initialization->load(core->getWidth(), core->getHeight());
		}
		break;

	case 20:
		if (LOGIN >= initState && LOGIN <= endState)
		{
			login = new Login;
			login->load(core->getWidth(), core->getHeight());
		}
		break;

	case 25:
		if (MENU >= initState && MENU <= endState)
		{
			menu = new Menu;
			menu->load(core->getWidth(), core->getHeight());
		}
		break;

	case 35:
		if (LEVELMENU >= initState && LEVELMENU <= endState)
		{
			levelMenu = new LevelMenu;
			levelMenu->load(core->getWidth(), core->getHeight());
		}
		break;

		//	case 71:
		//	play = new Play;
		//	play->load( core->getWidth(), core->getHeight() );
		//	break;

		//	case 95:
		//	table = new Table;
		//	table->load( core->getWidth(), core->getHeight() );
		//	break;

		//	case 96:
		//	editor = new Editor;
		//	editor->load( core->getWidth(), core->getHeight() );
		//	break;

	case 101:
		loading->beReady();
		break;
	}

	if (loading->isReady())
	{
		delete loading;
		loading = NULL;
		core->state = initState;	// SET FIRST STATE.
	}
}

void Engine::events()
{
	while (core->isEvent())
	{
		if (core->getEvent().type == sf::Event::Closed)
		{
			core->open = false;
		}

		switch (core->state)
		{
		case LOGIN: 	login->handle(core->getEvent()); 		break;
		case MENU: 		menu->handle(core->getEvent()); 		break;
		case LEVELMENU: levelMenu->handle(core->getEvent());	break;
			/*case PLAY: 		play->handle( core->getEvent() ); 	break;
			case TABLE: 	table->handle( core->getEvent() ); 	break;*/
		}
	}
}

void Engine::states()
{
	switch (core->state)
	{
	case LOADING:
		load();
		break;

	case INIT:
		initialization->mechanics(core->getElapsedTime());
		initialization->draw(core->getWindow());
		if (initialization->isNext())
		{
			core->state = LOGIN > endState ? -2 : LOGIN;
			delete initialization;
			initialization = nullptr;
		}
		break;

	case LOGIN:
		login->mechanics(core->getElapsedTime());
		login->draw(core->getWindow());
		if (login->isNext())	core->state = MENU > endState ? -2 : MENU;
		break;

	case MENU:
		menu->mechanics(core->getElapsedTime());
		menu->draw(core->getWindow());
		/*if (menu->isPrev()) // add editor exe
		else */if (menu->isNext())
		{
			levelMenu->reset();
			core->state = LEVELMENU > endState ? -2 : LEVELMENU;
		}
		else if (menu->isExit())	core->open = false;
		break;

	case LEVELMENU:
		levelMenu->mechanics(core->getElapsedTime());
		levelMenu->draw(core->getWindow());
		if (levelMenu->isPrev())
		{
			menu->reset();
			core->state = MENU < initState ? -2 : MENU;
		}
		else if (levelMenu->isNext())	core->state = PLATFORM > endState ? -2 : PLATFORM;
		else if (levelMenu->isExit())	core->open = false;
		break;

	default: break;
	}

	/*if( core->getState() == PLAY )
	{
	play->loadSound();
	play->head( core->getWindow(), core->getElapsedTime() );

	if( play->isMenu() )
	{
	play->saveSound();
	core->getState() = MENU;
	}
	else if( play->isLevel() )
	{
	play->saveSound();
	core->getState() = LEVEL;
	}
	else if( play->isTable() )
	{
	play->saveSound();
	core->getState() = TABLE;
	}
	else if( play->isEditor() )
	{
	play->saveSound();
	core->getState() = EDITOR;
	}
	}

	if( core->getState() == TABLE )
	{
	table->loadSound();
	table->head( core->getWindow(), core->getElapsedTime() );

	if( table->isMenu() )
	{
	table->saveSound();
	core->getState() = MENU;
	}
	else if( table->isLevel() )
	{
	table->saveSound();
	core->getState() = LEVEL;
	}
	}

	if( core->getState() == EDITOR )
	{
	editor->head( core->getWindow(), core->getElapsedTime() );

	if( editor->isBack() )
	{
	core->getState() = MENU;
	}
	else if( editor->isPlay() )
	{
	core->getState() = PLAY;
	play->setMessage( editor->getMessage() );
	}
	}*/
}