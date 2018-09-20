#include "core.h"
#include "loading.h"
#include "foefactory.h"
#include "fps.h"

cmm::Core* core = new cmm::Core(0, sf::Color(21, 21, 29, 0xFF));
FoeFactory* foeFactory = new FoeFactory;
std::vector<cmm::State*> states;
sf::Rect<float>* character = new sf::Rect<float>;
sf::Rect<float>* characterAttack = new sf::Rect<float>;
sf::RectangleShape charRect;
sf::RectangleShape charAttackRect;
FPS fps;
bool makeUpdate = true;
bool characterHasAttacked = false;
float characterDamage = 0;
float characterArmour = 1;
float characterHP = 1000;

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
		case 30:
			foeFactory->load(screen_w, screen_h);

			character->left = -1000;
			character->top = -1000;
			character->width = 100;
			character->height = 100;

			characterAttack->left = -1000;
			characterAttack->top = -1000;
			characterAttack->width = 50;
			characterAttack->height = 50;

			charRect.setFillColor(sf::Color(0xFF, 0xFF, 0xFF, 50));
			charAttackRect.setFillColor(sf::Color(0xFF, 0, 0, 30));
			charRect.setSize(sf::Vector2f(character->width, character->height));
			charAttackRect.setSize(sf::Vector2f(characterAttack->width, characterAttack->height));

			fps.load(core->getWidth(), core->getHeight());
			fps.setRightTop();
			fps.setActive(true);
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
	double elapsedTime = 0;
	while (core->open)
	{
		// clear
		elapsedTime = core->getElapsedTime();
		core->clear();

		// events, mouse, keyboard
		while (core->isEvent())
		{
			if (core->getEvent().type == sf::Event::Closed)
				core->open = false;

			if (core->getEvent().type == sf::Event::MouseButtonPressed)
			{
				if (core->getEvent().mouseButton.button == sf::Mouse::Left)
				{
					characterHasAttacked = true;
				}
				else if (core->getEvent().mouseButton.button == sf::Mouse::Right)
				{
					makeUpdate = !makeUpdate;
				}
			}

			if (core->getEvent().type == sf::Event::MouseMoved)
			{
				if (makeUpdate)
				{
					character->left = static_cast<float>(core->getEvent().mouseMove.x) - (character->width / 2);
					character->top = static_cast<float>(core->getEvent().mouseMove.y) - (character->height / 2);
				}
			}
		}

		characterAttack->left = character->left + characterAttack->width / 2;
		characterAttack->top = character->top + characterAttack->height / 2;

		charRect.setPosition(sf::Vector2f(character->left, character->top));
		charAttackRect.setPosition(sf::Vector2f(characterAttack->left, characterAttack->top));
		core->getWindow()->draw(charRect);
		core->getWindow()->draw(charAttackRect);

		fps.draw(core->getWindow());
		fps.mechanics(elapsedTime);

		foeFactory->setBorders(0, 0);
		foeFactory->update(core->getWindow(), elapsedTime,
			character, characterAttack, characterHasAttacked, characterDamage, characterHP,
			characterArmour);

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
	delete foeFactory;
	return 0;
}