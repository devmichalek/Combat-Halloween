#include "foefactory.h"

FoeFactory::FoeFactory()
{
	XYQuadTree = nullptr;
	free();
}

FoeFactory::~FoeFactory()
{
	free();
}

void FoeFactory::free()
{
	screen_w = 0;
	screen_h = 0;
	
	if(XYQuadTree)
	{
		delete XYQuadTree;
		XYQuadTree = nullptr;
	}
}

void FoeFactory::reset()
{

}

void FoeFactory::load(float screen_w, float screen_h)
{

}

void FoeFactory::draw(sf::RenderWindow* &window)
{

}

void FoeFactory::mechanics(double elapsedTime)
{

}