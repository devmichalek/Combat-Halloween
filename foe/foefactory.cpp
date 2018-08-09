#include "foefactory.h"
#include "skeleton.h"

FoeFactory::FoeFactory()
{
	tree = nullptr;
	res = nullptr;
	resBulk = nullptr;
	free();
}

FoeFactory::~FoeFactory()
{
	free();
}

void FoeFactory::free()
{
	if(res)
	{
		delete res;
		res = nullptr;
	}

	if (resBulk)
	{
		delete resBulk;
		resBulk = nullptr;
	}

	if (tree)
	{
		delete tree;
		tree = nullptr;
	}
}

void FoeFactory::reset()
{
	tree->incinerate();
}

void FoeFactory::load(const float &screen_w, const float &screen_h)
{
	free();

	res = new sf::Rect<float>;
	resBulk = new sf::Rect<float>;

	res->width = screen_w;
	res->height = screen_h;
	resBulk->width = screen_w * 2;
	resBulk->height = screen_h * 2;

	tree = new FoeTree;

	
	std::vector<int> states;	// 3 for example APPEAR, IDLE, WALK
	std::vector<int> offsets;	// 10, 12, 8
	std::vector<std::string> paths;	// skeleton, zombie, vampire etc.

	// skeleton test
	states.push_back(5);
	offsets.push_back(10);
	offsets.push_back(6);
	offsets.push_back(8);
	offsets.push_back(8);
	offsets.push_back(8);
	paths.push_back("images/deleteme/foes/skeleton/");
	tree->load(paths, states, offsets);

	FoeNode* foeNode = nullptr;

	int counter = 0;

	foeNode = new Skeleton;
	foeNode->ID = counter++;
	foeNode->cX = 200;
	foeNode->cY = 200;
	foeNode->setSpriteType(0);
	foeNode->setSpriteLines(offsets);
	foeNode->setScale(0.5);
	foeNode->setWidth(78);
	foeNode->setPosition(200, screen_h - 150);
	foeNode->setBorders(0, 1000);
		
	foeNode->setArmour(10);
	foeNode->setDamage(10);
	foeNode->setVelocity(10);
	foeNode->setHeartPoints(100);
	foeNode->setBoxes();

	tree->insert(foeNode);
}

// Process ------------------------
void FoeFactory::processData(	sf::RenderWindow* &window,
								double elapsedTime,
								Rect* &character,
								Rect* &characterAttack,
								bool &characterHasAttacked,
								float &characterDamage,
								float &characterHP,
								float &characterArmour
							)
{
	tree->processData(window, elapsedTime, resBulk, character, characterAttack, characterHasAttacked,
		characterDamage, characterHP, characterArmour);
	tree->process();
}



void FoeFactory::setBorderX(const float &newX)
{
	res->left = newX;
	resBulk->left = newX - res->width / 2;
}

void FoeFactory::setBorderY(const float &newY)
{
	res->top = newY;
	resBulk->top = newY - res->height / 2;
}

void FoeFactory::setBorders(const float &newX, const float &newY)
{
	setBorderX(newX);
	setBorderY(newY);
}