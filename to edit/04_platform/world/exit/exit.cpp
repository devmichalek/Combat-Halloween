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
	screen_w = 0;
	next = false;
	main_x = 0;
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
}


void Exit::positioning( float right, int screen_w )
{
	main_x = right -screen_w /2;
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
	if( x > main_x )
	{
		// main_x = 0;
		next = true;
		// printf( "yeap\n" );
	}
}

bool Exit::nextState()
{
	return next;
}