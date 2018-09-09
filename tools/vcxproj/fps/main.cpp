#include "core.h"
#include "loading.h"
#include "fps.h"

cmm::Core* core = new cmm::Core(0, sf::Color(21, 21, 29, 0xFF));
std::vector<cmm::State*> states;
FPS fps;

// Note: FPS is built into chat class, so it can be easily turn on by command "@fps".
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
		case 50:
			fps.load(core->getWidth(), core->getHeight());
			fps.setActive(true);

			//fps.setLeftTop();
			//fps.setRightTop();
			fps.setLeftBot();
			//fps.setRightBot();
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
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(core->getWidth() / 10, core->getHeight() / 10));
	shape.setFillColor(sf::Color::Black);

	float velocity = 120;
	sf::Vector2f pos(0, 0);
	sf::Vector2f dest(core->getWidth() / 2, core->getHeight() / 2);

	float counter = 0;
	int counter_line = 4;

	while (core->open)
	{
		// clear
		core->clear();

		// events, mouse, keyboard
		while (core->isEvent())
		{
			if (core->getEvent().type == sf::Event::Closed)
				core->open = false;
		}

		fps.mechanics(core->getElapsedTime());
		fps.draw(core->getWindow());

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