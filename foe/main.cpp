#include "core.h"
#include "foefactory.h"

Core* core = new Core(0, sf::Color(21, 21, 29, 0xFF));
FoeFactory* foeFactory = new FoeFactory;

enum STATES
{
	LEVELMENU = 4,
	PLATFORM,
	ENDSCENE
};

int main(int argc, char** argv)
{
	core->create("Combat Halloween");
	core->state = PLATFORM;
	float screen_w = core->getWidth();
	float screen_h = core->getHeight();
	foeFactory->load(screen_w, screen_h);

	sf::Rect<float>* character = new sf::Rect<float>;
	character->left = -1000;
	character->top = -1000;
	character->width = 100;
	character->height = 100;

	sf::Rect<float>* characterAttack = new sf::Rect<float>;
	characterAttack->left = -1000;
	characterAttack->top = -1000;
	characterAttack->width = 50;
	characterAttack->height = 50;

	bool characterHasAttacked = false;
	float characterDamage = 0;
	float characterArmour = 1;
	float characterHP = 1000;

	sf::RectangleShape charRect;
	sf::RectangleShape charAttackRect;
	charRect.setFillColor(sf::Color(0xFF, 0xFF, 0xFF, 50));
	charAttackRect.setFillColor(sf::Color(0xFF, 0, 0, 30));
	charRect.setSize(sf::Vector2f(character->width, character->height));
	charAttackRect.setSize(sf::Vector2f(characterAttack->width, characterAttack->height));

	while (core->open)
	{
		characterHasAttacked = false;

		// clear
		core->clear();

		// events, mouse, keyboard
		while (core->isEvent())
		{
			if (core->getEvent().type == sf::Event::Closed)
			{
				core->open = false;
			}

			if (core->getEvent().type == sf::Event::MouseButtonPressed)
			{
				if (core->getEvent().mouseButton.button == sf::Mouse::Left)
				{
					characterHasAttacked = true;
				}
			}

			if (core->getEvent().type == sf::Event::MouseMoved)
			{
				character->left = static_cast<float>(core->getEvent().mouseMove.x) - (character->width / 2);
				character->top = static_cast<float>(core->getEvent().mouseMove.y) - (character->height / 2);
			}
		}

		characterAttack->left = character->left + characterAttack->width / 2;
		characterAttack->top = character->top + characterAttack->height / 2;

		charRect.setPosition(sf::Vector2f(character->left, character->top));
		charAttackRect.setPosition(sf::Vector2f(characterAttack->left, characterAttack->top));
		core->getWindow()->draw(charRect);
		core->getWindow()->draw(charAttackRect);


		if (core->state == PLATFORM)
		{
			foeFactory->setBorders(0, 0);
			foeFactory->processData(core->getWindow(), core->getElapsedTime(),
				character, characterAttack, characterHasAttacked, characterDamage, characterHP,
				characterArmour);
		}


		core->display();
	}

	delete core;
	delete foeFactory;
	return 0;
}