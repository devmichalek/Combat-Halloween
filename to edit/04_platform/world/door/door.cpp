#include "04_platform/world/door/door.h"
#include "file/file.h"

Door::Door()
{
	free();
}

Door::~Door()
{
	free();
}

void Door::free()
{
	next = false;
	sprite.free();
}

void Door::reset( int distance )
{
	next = false;
	sprite.setPosition( sprite.getX() +distance, sprite.getY() );
}



void Door::load( int type )
{
	free();
	
	sprite.setName( "door-sprite" );
	sprite.load( "data/04_platform/world/" +con::itos( type ) +"/door.png" );
}

void Door::draw( sf::RenderWindow* &window )
{
	window->draw( sprite.get() );
}

void Door::positioning( Rect* rect )
{
	if( rect != NULL )
	{
		sprite.setPosition( rect->getX() +rect->getWidth() /2 -sprite.getWidth() /2, rect->getY() -sprite.getHeight() );
	}
}



void Door::fadein( int v, int max )
{
	sprite.fadein( v, max );
}

void Door::fadeout( int v, int min )
{
	sprite.fadeout( v, min );
}




void Door::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		sprite.setPosition( sprite.getX() +vel, sprite.getY() );
	}
	else if( direction == 2 )
	{
		sprite.setPosition( sprite.getX() -vel, sprite.getY() );
	}
}

void Door::undoFall( sf::Uint8 add )
{
	sprite.setPosition( sprite.getX() +add, sprite.getY() );
}

void Door::setColor( sf::Color color )
{
	sprite.setColor( color );
}

void Door::checkHero( Rect* rect )
{
	if( sprite.checkRectCollision( *rect ) )
	{
		// printf( "happened\n" );
		next = true;
	}
}

bool Door::nextState()
{
	return next;
}