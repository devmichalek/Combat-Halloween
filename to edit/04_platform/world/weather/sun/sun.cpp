#include "04_platform/world/weather/sun/sun.h"


Sun::Sun()
{
	sun = NULL;
	free();
}

Sun::~Sun()
{
	free();
}

void Sun::free()
{
	if( sun != NULL )
	{
		delete sun;
		sun = NULL;
	}
	
	alpha = 0;
	angle = 0;
}

void Sun::reset()
{
	alpha = 0;
	angle = 0;
}



void Sun::load( int screen_w, int screen_h )
{
	free();

	sun = new sf::CircleShape( 150 );
	sun->setFillColor( sf::Color( 0xFF, 0xFF, 0xFF, 0 ) );
	sun->setPosition( screen_w /2, screen_h );
	sun->setOrigin( 650, 650 );
	setStartAngle();
}

void Sun::draw( sf::RenderWindow* &window )
{
	window->draw( *sun );
	sun->setRotation( angle );
	
	angle += 0.033; // 0.001833333
	if( angle > 360 )
		angle = 0;
}



void Sun::fadein( int v, int max )
{
	alpha += v;
	if( alpha >= max )
	{
		alpha = max;
	}
	
	sf::Color c = sun->getFillColor();
	c.a = alpha;
	sun->setFillColor( c );
}

void Sun::fadeout( int v, int min )
{
	alpha -= v;
	if( alpha <= min )
	{
		alpha = min;
	}
	
	sf::Color c = sun->getFillColor();
	c.a = alpha;
	sun->setFillColor( c );
}

void Sun::setColor( sf::Color color )
{
	sf::Color c = sun->getFillColor();
	c.r = color.r;
	c.g = color.g;
	c.b = color.b;
	
	sun->setFillColor( c );
}

void Sun::setStartAngle()
{
	angle = -20;
	sun->setRotation( angle );
}