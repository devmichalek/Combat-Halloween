#include "foetree.h"

FoeTree::FoeTree()
{
	cleanProcessedData();
}

FoeTree::~FoeTree()
{
	if (!sprites.empty())
	{
		sprites.clear();
		sprites.shrink_to_fit();
	}
	
	cleanProcessedData();
}

void FoeTree::load(std::vector<std::vector<cmm::Sprite*>> newSprites)
{
	sprites = newSprites;
}



// Process ------------------------
void FoeTree::processData(	sf::RenderWindow* &window,
							double &elapsedTime,
							Rect* &screen,
							Rect* &character,
							Rect* &characterAttack,
							bool &characterHasAttacked,
							float &characterDamage,
							float &characterHP,
							float &characterArmour
						)
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

void FoeTree::process()
{
	processPrivate(root);
}

void FoeTree::cleanProcessedData()
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



bool FoeTree::containsPrivate(Quad* quad, Rect* rect)
{
	if (!quad)										return false;	// quad does not exist
	if(quad->node->cX < rect->left)					return false;	// point is on the left outside of area
	if (quad->node->cX > rect->left + rect->width)	return false;	// point is on the right outside of area
	if (quad->node->cY < rect->top)					return false;	// point is above the area
	if (quad->node->cY > rect->top + rect->height)	return false;	// point is below the area
	return true;
}

void FoeTree::processPrivate(Quad* quad)
{
	// Check if particular foe is inside of visible for player area
	// We keep searching if particular quad is inside of visible area
	if (containsPrivate(quad->topLeft))		processPrivate(quad->topLeft);
	if (containsPrivate(quad->topRight))	processPrivate(quad->topRight);
	if (containsPrivate(quad->botLeft))		processPrivate(quad->botLeft);
	if (containsPrivate(quad->botRight))	processPrivate(quad->botRight);

	// At this point a particular quad has no children so we do stuff here
	// Here we send all the data that each foe needs
	// To make it as much flexible we call one function that all the foes have
	// And inside of this function a foe does whatever it wants
	// Giving feedback of all the actions that has taken place

	int s = quad->node->getSpriteState();	// Foe's state e. g. IDLE, ATTACK etc.

	if (s < 0)
		return;

	quad->node->mechanics(	elapsedTime,
							character,
							characterAttack,
							characterHasAttacked,
							characterDamage,
							characterHP,
							characterArmour
						 );


	// Draw
	int t = quad->node->getSpriteType();	// Foe's type e. g. SKELETON, ZOMBIE etc.
	float sc = quad->node->getScale();
	sprites[t][s]->setScale(sc, sc);
	sprites[t][s]->setOffset(quad->node->getSpriteOffset());
	sprites[t][s]->setPosition(quad->node->getSpriteX(), quad->node->getSpriteY());
	window->draw(sprites[t][s]->get()/*, &shader*/);
}