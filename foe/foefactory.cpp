#include "foefactory.h"

FoeFactory::FoeFactory()
{
	tree = nullptr;
	free();
}

FoeFactory::~FoeFactory()
{
	free();
}

void FoeFactory::free()
{
	if(tree)
	{
		delete tree;
		tree = nullptr;
	}
}

void FoeFactory::reset()
{

}

void FoeFactory::load(const float &screen_w, const float &screen_h)
{
	free();

	res.width = screen_w;
	res.height = screen_h;
	resBulk.width = screen_w * 2;
	resBulk.height = screen_h * 2;

	tree = new FoeTree;
}

void FoeFactory::draw(sf::RenderWindow* &window)
{

}

void FoeFactory::mechanics(const double &elapsedTime)
{

}



void FoeFactory::setBorderX(const float &newX)
{
	res.left = newX;
	resBulk.left = newX - res.width / 2;
}

void FoeFactory::setBorderY(const float &newY)
{
	res.top = newY;
	res.top = newY - res.height / 2;
}

void FoeFactory::setBorders(const float &newX, const float &newY)
{
	setBorderX(newX);
	setBorderY(newY);
}