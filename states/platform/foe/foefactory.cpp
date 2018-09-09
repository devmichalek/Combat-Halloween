#include "foefactory.h"
#include "skeleton.h"
#include "zombie.h"

FoeFactory::FoeFactory()
{
	resolution = nullptr;
	wrapper = nullptr;
	free();
}

FoeFactory::~FoeFactory()
{
	free();
}

void FoeFactory::free()
{
	if(resolution)
	{
		delete resolution;
		resolution = nullptr;
	}

	if (wrapper)
	{
		delete wrapper;
		wrapper = nullptr;
	}
}

void FoeFactory::reset()
{
	wrapper->incinerate();
}

void FoeFactory::load(const float &screen_w, const float &screen_h)
{
	free();

	resolution = new sf::Rect<float>;

	resolution->width = screen_w;
	resolution->height = screen_h;

	wrapper = new FoeWrapper;

	
	std::vector<int> states;	// 3 for example APPEAR, IDLE, WALK
	std::vector<int> offsets;	// 10, 12, 8
	std::vector<std::string> paths;	// skeleton, zombie, vampire etc.

	states.push_back(5);

	// Skeleton
	/*offsets.push_back(10);
	offsets.push_back(6);
	offsets.push_back(8);
	offsets.push_back(8);
	offsets.push_back(8);
	paths.push_back("images/deleteme/foes/skeleton/");*/

	// Zombie
	offsets.push_back(11);
	offsets.push_back(6);
	offsets.push_back(10);
	offsets.push_back(7);
	offsets.push_back(8);
	paths.push_back("images/deleteme/foes/zombie/");

	wrapper->load(paths, states, offsets);

	Foe* foe = nullptr;

	int counter = 0;

	foe = new Zombie;
	foe->setSpriteType(0);
	foe->setSpriteLines(offsets);
	foe->setScale(0.5);
	foe->setWidth(66);
	foe->setPosition(200, screen_h - 500);
	foe->setLeft(0);
	foe->setRight(screen_w);
	foe->setFeatures({ "10", "10", "100", "100", "4", "2" });
	foe->marshial();
	wrapper->insert(foe);
}

// Process ------------------------
void FoeFactory::update(sf::RenderWindow* &window,
						double elapsedTime,
						Rect* &character,
						Rect* &characterAttack,
						bool &characterHasAttacked,
						float &characterDamage,
						float &characterHP,
						float &characterArmour)
{
	wrapper->update(window, elapsedTime, resolution, character, characterAttack, characterHasAttacked,
					characterDamage, characterHP, characterArmour);
	wrapper->process();
}



void FoeFactory::setBorderX(const float &newX)
{
	resolution->left = newX;
}

void FoeFactory::setBorderY(const float &newY)
{
	resolution->top = newY;
}

void FoeFactory::setBorders(const float &newX, const float &newY)
{
	setBorderX(newX);
	setBorderY(newY);
}