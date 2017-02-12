#include "torch.h"

Torch::Torch()
{
	active = false;
}

Torch::~Torch()
{
	free();
}

void Torch::free()
{
	light.free();
	active = false;
}



void Torch::load()
{
	light.setName( "torch-light" );
	light.load( "data/sprites/hero/light.png" );
	light.setAlpha( 0xFF );
}

void Torch::setPosition( Rect* rect )
{
	if( rect != NULL )
	{
		light.setPosition( rect->getX() +rect->getWidth()/2 -light.getWidth()/2, rect->getY() +rect->getHeight()/2 -light.getHeight()/2 );
	}
}

void Torch::drawTest( sf::RenderWindow* &window )
{
	window->draw( light.get() );
}



Rect* Torch::getRect()
{
	Rect* rect = new Rect;
	rect->set( light.getX(), light.getY(), light.getWidth(), light.getHeight() );
	
	return rect;
}

sf::Image* Torch::getImage()
{
	return light.getImage();
}