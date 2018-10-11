#include "engine.h"

Engine::Engine()
{
	// Set seed.
	srand(static_cast<int>(time(nullptr)));

	// Init only loading state. It launches the console and checks basic files.
	this->states.push_back(new Loading);
	if (Loading::isError())
		return;

	// Set core.
	core = std::make_unique<cmm::Core>(cmm::LOADING, cmm::BACKGROUND_COLOR);
	core->create("Combat Halloween");
	core->setIcon("images/icons/icon.png");

	// Continue by loading the Loading module.
	this->states[cmm::LOADING]->load(core->getWidth(), core->getHeight());
}

Engine::~Engine()
{
	for (auto &it : this->states)
	{
		delete it;
		it = nullptr;
	}

	this->states.clear();
}

void Engine::loading_loop()
{
	float screen_w = (float)core->getWidth();
	float screen_h = (float)core->getHeight();

	while (core->open)
	{
		while (core->isEvent())
		{
			if (core->getEvent().type == sf::Event::Closed)
				core->open = false;
		}

		this->states[core->state]->draw(core->getWindow());
		this->states[core->state]->mechanics(core->getElapsedTime());

		switch (LoadingState::getState())
		{
		case 5:		this->states.push_back(new Initialization);
					this->states[cmm::INIT]->load(screen_w, screen_h);
					break;

		case 15:	this->states.push_back(new Login);
					this->states[cmm::LOGIN]->load(screen_w, screen_h);
					break;

		case 28:	this->states.push_back(new Menu);
					this->states[cmm::MENU]->load(screen_w, screen_h);
					break;

		case 36:	this->states.push_back(new LevelMenu);
					this->states[cmm::LEVELMENU]->load(screen_w, screen_h);
					break;

		case 52:	this->states.push_back(new Platform);
					this->states[cmm::PLATFORM]->load(screen_w, screen_h);
					break;

		case 60:	this->states.push_back(nullptr);
					//this->states[cmm::TABLE]->load(screen_w, screen_h);
					break;

		case 78:	this->states.push_back(new Editor);
					this->states[cmm::EDITOR]->load(screen_w, screen_h);
					break;

		case 80:	this->states.push_back(new Simulator);
					this->states[cmm::SIMULATOR]->load(screen_w, screen_h);
					break;
		}

		this->states[core->state]->setState(core->state);
		if (core->state != cmm::LOADING)	// Game starts here.
			break;
	}

	//delete states[cmm::LOADING];
	//states[cmm::LOADING] = nullptr;
	this->states.shrink_to_fit();
	core->state = cmm::INIT; // Start state;
}

void Engine::main_loop()
{
	while (core->open)
	{
		// clear
		core->clear();

		// events, mouse, keyboard
		while (core->isEvent())
		{
			if (core->getEvent().type == sf::Event::Closed)
				core->open = false;

			this->states[core->state]->handle(core->getEvent());
		}

		this->states[core->state]->mechanics(core->getElapsedTime());
		this->states[core->state]->draw(core->getWindow());
		this->states[core->state]->setState(core->state);

		// display
		core->display();
	}
}