#include "exit.h"
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
	screen_w = 0;
	next = false;
	main_x = 0;
	rhythm.free();
}

void Exit::reset( int distance )
{
	next = false;
	main_x += distance;
}



void Exit::load( int width, int screen_w )
{
	free();
	
	this->screen_w = screen_w;
	main_x = 0;
	
	rhythm.setName( "exit-rhythm" );
	rhythm.load( "data/platform/world/sounds/exit/0.wav" );
}


void Exit::positioning( float right )
{
	main_x = right;
}



void Exit::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		main_x += vel;
	}
	else if( direction == 2 )
	{
		main_x -= vel;
	}
}

void Exit::undoFall( sf::Uint8 add )
{
	main_x += add;
}


void Exit::checkHero( float x )
{
	// printf( "%f %f\n", x, main_x  );
	if( x > main_x && !next )
	{
		if( rhythm.isPlayable() )
		{
			rhythm.play();
		}
		
		next = true;
		// printf( "yeap\n" );
	}
}

bool Exit::nextState()
{
	return next;
}




void Exit::turn()
{
	rhythm.turn();
}

void Exit::turnOn()
{
	rhythm.turnOn();
}

void Exit::turnOff()
{
	rhythm.turnOff();
}

void Exit::setVolume( int v )
{
	rhythm.setVolume( v );
}