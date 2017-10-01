#include "lightpoint.h"

LightPoint::LightPoint( float x, float y )
{
	this->x = x;
	this->y = y;
	radius = 100;
	velocity = 100;
	color = sf::Color::White;
	
	if( !points.empty() )
	{
		points.clear();
	}
}

LightPoint::~LightPoint()
{
	x = 0;
	y = 0;
	radius = 0;
	velocity = 0;
	color = sf::Color::White;
	
	if( !points.empty() )
	{
		points.clear();
	}
}