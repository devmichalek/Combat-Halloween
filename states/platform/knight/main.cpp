#include "core.h"
#include "loading.h"
#include "knight.h"
#include "tiles.h"	// to test basic collisions

cmm::Core* core = new cmm::Core(0, sf::Color(21, 21, 29, 0xFF));
std::vector<cmm::State*> states;
Knight* knight = new Knight;
Tiles tiles;

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
			knight->load(core->getWidth(), core->getHeight());
			knight->set(core->getWidth() / 2, core->getHeight() / 2);
			knight->switchCollision();
			break;
		case 75:
			const int max = 3000;
			char** t, **un;

			t = new char*[max];
			un = new char*[max];
			for (int i = 0; i < max; ++i)
			{
				t[i] = new char[max];
				un[i] = new char[max];
				for (int j = 0; j < max; ++j)
				{
					t[i][j] = -1;
					un[i][j] = -1;
				}
			}

			t[0][1] = 0;
			t[2][1] = 1;
			t[4][1] = 1;
			t[6][1] = 1;
			t[8][1] = 1;
			t[10][1] = 1;
			t[12][1] = 1;
			t[14][1] = 1;
			t[16][1] = 1;
			t[18][1] = 1;

			tiles.load(core->getWidth(), core->getHeight());
			tiles.fill(t, un);
			tiles.switchCollision();
			
			for (int i = 0; i < max; ++i)
			{
				delete[] t[i];
				delete[] un[i];
				t[i] = nullptr;
				un[i] = nullptr;
			}
			delete[] t;
			delete[] un;
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
		// clear
		core->clear();

		// events, mouse, keyboard
		while (core->isEvent())
		{
			if (core->getEvent().type == sf::Event::Closed)
				core->open = false;

			knight->handle(core->getEvent());
		}

		// mechanics
		knight->mechanics(core->getElapsedTime());
		knight->gravity();
		if (tiles.checkCollision(knight->getRect()))
			knight->undoGravity();

		// draw
		tiles.draw(core->getWindow());
		knight->draw(core->getWindow());

		// display
		core->display();
	}
}

int main(int argc, char** argv)
{
	int x = 10;
	x = ++x + x++;

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