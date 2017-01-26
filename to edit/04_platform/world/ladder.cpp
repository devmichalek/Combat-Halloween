#include "ladder.h"
#include <cstdlib>





Ladder::Ladder()
{
	red = green = blue = add = 0;
}

Ladder::~Ladder()
{
	free();
}

void Ladder::free()
{
	for( unsigned i = 0; i < ladder.size(); i++ )
	{
		ladder[ i ]->free();
	}
	
	ladder.clear();
	ladders.clear();
	
	red = green = blue = add = 0;
}


void Ladder::load( int type )
{
	free();
	
	for( int i = 0; i < 2; i++ )
	{
		ladder.push_back( new MySprite() );
		ladder[ i ]->setName( "ladder[" +to_string( i ) +"]" );
		ladder[ i ]->loadByImage( "data/sprites/play/ladder/" +to_string( i ) +".png" );
	}
	
	// setColor
	if( type == 0 )
	{
		red = 0;
		green = 0xFF;
		blue = 0xAA;
	}
	else if( type == 1 )
	{
		red = 0xFF;
		green = 0x9C;
		blue = 0x50;
	}
	else if( type == 2 )
	{
		red = 0;
		green = 0xFF;
		blue = 0xFF -0xAA;
		add = 0xAA;
	}
	else if( type == 3 )
	{
		red = 0xFF;
		green = 0xFF;
		blue = 0xAA;
	}
}

void Ladder::draw( sf::RenderWindow* &window, int screen_w )
{
	for( unsigned i = 0; i < ladders.size(); i++ )
	{
		if( ladders[ i ]->x > -screen_w/2 && ladders[ i ]->x < screen_w )
		{
			ladder[ ladders[ i ]->nr ]->setPosition( ladders[ i ]->x, ladders[ i ]->y );
			ladder[ ladders[ i ]->nr ]->setColor( sf::Color( ladders[ i ]->red, ladders[ i ]->green, ladders[ i ]->blue ) );
			window->draw( ladder[ ladders[ i ]->nr ]->get() );
		}
	}
}


void Ladder::fadein( int v, int max )
{
	for( unsigned i = 0; i < ladder.size(); i++ )
	{
		ladder[ i ]->fadein( v, max );
	}
}

void Ladder::fadeout( int v, int min )
{
	for( unsigned i = 0; i < ladder.size(); i++ )
	{
		ladder[ i ]->fadeout( v, min );
	}
}


int Ladder::strToInt( string s )
{
	bool m=false;
    int tmp=0;
    unsigned i=0;
    if(s[0]=='-')
    {
          i++;
          m = true;
    }
	
    while(i<s.size())
    {
      tmp = 10*tmp+s[i]-48;
      i++;
    }
	
    return m ? -tmp : tmp; 
}

void Ladder::positioning(  vector <Plank*> planks )
{
	ladders = planks;
	
	for( unsigned i = 0; i < ladders.size(); i++ )
	{
		ladders[ i ]->red = red;
		ladders[ i ]->green = green;
		ladders[ i ]->blue = rand()%blue +add;
	}
}


void Ladder::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( unsigned i = 0; i < ladders.size(); i++ )
		{
			ladders[ i ]->x += vel;
		}
	}
	else if( direction == 2 )
	{
		for( unsigned i = 0; i < ladders.size(); i++ )
		{
			ladders[ i ]->x -= vel;
		}
	}
}

int Ladder::backToGrass( int add )
{
	for( unsigned i = 0; i < ladders.size(); i++ )
	{
		ladders[ i ]->x += add;
	}
	
	return add;
}

void Ladder::addLadder( int x, int y )
{
	// add ladder.
	ladders.push_back( new Plank() );
	
	// set x.
	ladders[ ladders.size()-1 ]->x = x;
	
	// set y.
	ladders[ ladders.size()-1 ]->y = y;
	
	ladders[ ladders.size()-1 ]->red;
	ladders[ ladders.size()-1 ]->green;
	ladders[ ladders.size()-1 ]->blue = rand()%blue +add;
}

bool Ladder::checkLadder( Rect* rect, int screen_w )
{
	if( rect != NULL )
	{
		for( unsigned i = 0; i < ladders.size(); i++ )
		{
			if( ladders[ i ]->x > -screen_w/2 && ladders[ i ]->x < screen_w )
			{
				ladder[ ladders[ i ]->nr ]->setPosition( ladders[ i ]->x, ladders[ i ]->y );
				if( ladder[ ladders[ i ]->nr ]->checkCollision( rect->getX() +rect->getWidth() /4, rect->getY() -50, rect->getWidth() /2, rect->getHeight() ) )
				{
					return true;
				}
			}
		}
	}
	
	return false;
}

int Ladder::getW( sf::Uint8 nr )
{
	return ladder[ nr ]->getWidth();
}

int Ladder::getH( sf::Uint8 nr )
{
	return ladder[ nr ]->getHeight();
}
