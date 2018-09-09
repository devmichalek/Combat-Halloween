#include "core.h"
#include "loading.h"
#include "initialization.h"
#include "login.h"

cmm::Core* core = new cmm::Core(0, sf::Color(21, 21, 29, 0xFF));
std::vector<cmm::State*> states;

// Load function.
void loading_loop()
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

		states[core->state]->draw(core->getWindow());
		states[core->state]->mechanics(core->getElapsedTime());

		switch (LoadingState::getState())
		{
		case 1:
			states.push_back(new Initialization);
			states[cmm::INIT]->load(screen_w, screen_h);
			break;

		case 20:
			states.push_back(new Login);
			states[cmm::LOGIN]->load(screen_w, screen_h);
			break;
		}

		states[core->state]->setState(core->state);
		if (core->state != cmm::LOADING)// game starts from here
			break;	
	}

	//delete states[cmm::LOADING];
	//states[cmm::LOADING] = nullptr;
	states.shrink_to_fit();
}

void main_loop()
{
	while (core->open)
	{
		if (core->state == cmm::MENU)
			break;

		// clear
		core->clear();

		// events, mouse, keyboard
		while (core->isEvent())
		{
			if (core->getEvent().type == sf::Event::Closed)
				core->open = false;

			states[core->state]->handle(core->getEvent());
		}

		states[core->state]->mechanics(core->getElapsedTime());
		states[core->state]->draw(core->getWindow());
		states[core->state]->setState(core->state);

		// display
		core->display();
	}
}

int main(int argc, char** argv)
{
	// Init only loading state.
	states.push_back(new Loading);
	if (Loading::isError())
		return -1;
	
	// Create window.
	core->create("Combat Halloween");
	states[cmm::LOADING]->load(core->getWidth(), core->getHeight());

	// Loops.
	loading_loop();
	main_loop();

	// Free states.
	for (auto &it : states)
	{
		delete it;
		it = nullptr;
	}
	states.clear();
	delete core;
	return 0;
}