#include "foewrapper.h"

FoeWrapper::FoeWrapper()
{
	tree = nullptr;
	free();
}

FoeWrapper::~FoeWrapper()
{
	free();
}

void FoeWrapper::free()
{
	incinerate();

	if (!sprites.empty())
	{
		sprites.clear();
		sprites.shrink_to_fit();
	}

	clean();
}

void FoeWrapper::clean()
{
	window = nullptr;
	elapsedTime = 0;
	screen = nullptr;
	character = nullptr;
	characterAttack = nullptr;
	characterHasAttacked = false;
	characterDamage = 0;
	characterHP = 0;
	characterArmour = 0;
}

void FoeWrapper::incinerate()
{
	if (tree)
	{
		delete tree;
		tree = nullptr;
	}

	if (!foes.empty())
	{
		foes.clear();
		foes.shrink_to_fit();
	}
}



void FoeWrapper::insert(Foe* foe)
{
	if (!tree)
		return;

	foes.push_back(foe);
	
	// Create a box
	Box box(Point(foe->getLeft(), foe->getTop()), Point(foe->getRight(), foe->getBot()));

	// Insert new item
	tree->insert(std::make_pair(box, foes.size() - 1));
}

void FoeWrapper::load(std::vector<std::string> &str, std::vector<int> &s, std::vector<int>&o)
{
	free();

	// Create tree.
	tree = new RTree;

	// Insert sprites
	int counter = 0;
	std::vector<cmm::Sprite*> temp;
	for (int i = 0; i < (int)str.size(); ++i)
	{
		temp.clear();
		for (int j = 0; j < s[i]; ++j)
		{
			cmm::Sprite* sprite = new cmm::Sprite;
			sprite->load((str[i] + std::to_string(j) + ".png").c_str(), o[counter]);
			temp.push_back(sprite);
			++counter;
		}

		sprites.emplace_back(temp);
	}
}



void FoeWrapper::update(sf::RenderWindow* &window,
						double &elapsedTime,
						Rect* &screen,
						Rect* &character,
						Rect* &characterAttack,
						bool &characterHasAttacked,
						float &characterDamage,
						float &characterHP,
						float &characterArmour)
{
	this->window = window;
	this->elapsedTime = elapsedTime;
	this->screen = screen;
	this->character = character;
	this->characterAttack = characterAttack;
	this->characterHasAttacked = characterHasAttacked;
	this->characterDamage = characterDamage;
	this->characterHP = characterHP;
	this->characterArmour = characterArmour;
}

void FoeWrapper::process()
{
	std::vector<BoxID> result;
	Box queryBox(Point(screen->left, screen->top), Point(screen->left + screen->width, screen->top + screen->height));

	// Query
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));


	// At this point we have all foes that are inside of visible area (result)
	// Here we give all the data that each foe needs
	// To make it as much flexible we call one function that all the foes have
	// And inside of this function a foe does whatever it wants
	// Giving feedback of all the actions that has taken place
	Foe* foe;
	int ID = 0, s = 0, t = 0;
	BOOST_FOREACH(BoxID const& item, result)
	{
		ID = item.second;
		foe = foes[ID];
		foe->mechanics( elapsedTime,
						character,
						characterAttack,
						characterHasAttacked,
						characterDamage,
						characterHP,
						characterArmour);

		// Draw
		s = foe->getSpriteState();	// Foe's state e. g. IDLE, ATTACK etc.
		if (s < 0)	continue;		// Nothing to draw -> continue
		t = foe->getSpriteType();	// Foe's type e. g. SKELETON, ZOMBIE etc.

		sprites[t][s]->setScale(foe->getScaleX(), foe->getScaleY());
		sprites[t][s]->setOffset(foe->getSpriteOffset());
		sprites[t][s]->setPosition(foe->getSpriteX(), foe->getSpriteY());

		window->draw(sprites[t][s]->get()/*, &shader*/);
	}
}