#include "core.h"
#include "loading.h"
#include "pausesystem.h"
#include <SFML/Graphics/RectangleShape.hpp>

cmm::Core* core = new cmm::Core(0, cmm::BACKGROUND_COLOR);
std::vector<cmm::State*> states;
PauseSystem pauseSystem;


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
			pauseSystem.load(core->getWidth(), core->getHeight());
			pauseSystem.setVolume(50);
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
	shape.setFillColor(cmm::LOADING_COLOR);

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

			pauseSystem.handle(core->getEvent());
		}

		core->getWindow()->draw(shape);
		pauseSystem.draw(core->getWindow());

		// simple test system
		double elapsedTime = core->getElapsedTime();

		if (pauseSystem.isActive())
		{
			float value = static_cast<float>(elapsedTime) * MAX_ALPHA * 2;
			int min = static_cast<int>(MAX_ALPHA * 3 / 4);
			pauseSystem.fadein(value * 3, min);
		}
		else
		{
			float value = static_cast<float>(elapsedTime) * MAX_ALPHA * 2;
			int max = static_cast<int>(MAX_ALPHA), min = 0;
			pauseSystem.fadeout(value, min);

			if (pos.x < dest.x)
				pos.x += static_cast<float>(elapsedTime) * velocity;
			else
				pos.x -= static_cast<float>(elapsedTime) * velocity;

			if (pos.y < dest.y)
				pos.y += static_cast<float>(elapsedTime) * velocity;
			else
				pos.y -= static_cast<float>(elapsedTime) * velocity;

			shape.setPosition(pos);
		}

		counter += static_cast<float>(elapsedTime);
		if (counter > counter_line)
		{
			counter = 0;
			int x = rand() % 20 + 1;
			int y = rand() % 20 + 1;
			dest = sf::Vector2f(core->getWidth() / x, core->getHeight() / y);
		}

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