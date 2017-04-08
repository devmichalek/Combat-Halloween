#include "04_platform/world/exit/exit.h"
#include "file/file.h"

Exit::Exit()
{
	free();
}

Exit::~Exit()
{
	free();
}

void Exit::free()
{
	next = false;
	sprite.free();
}

void Exit::reset( int distance )
{
	next = false;
	sprite.setPosition( sprite.getX() +distance, sprite.getY() );
}



void Exit::load( int width )
{
	free();
	
	sprite.setName( "exit-sprite" );
	sprite.create( width, width );
}


void Exit::positioning( Rect* rect )
{
	if( rect != NULL )
	{
		sprite.setPosition( rect->getX() +rect->getWidth() /2 -sprite.getWidth() /2, rect->getY() -sprite.getHeight() );
	}
}



void Exit::moveX( sf::Uint8 direction, float vel )
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

void Exit::undoFall( sf::Uint8 add )
{
	sprite.setPosition( sprite.getX() +add, sprite.getY() );
}


void Exit::checkHero( Rect* rect )
{
	if( sprite.checkRectCollision( *rect ) )
	{
		next = true;
	}
}

bool Exit::nextState()
{
	return next;
}