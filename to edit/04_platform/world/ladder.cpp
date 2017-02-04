#include "ladder.h"
#include <cstdlib>
#include <fstream>

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
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
	
	if( !planks.empty() )
	{
		for( auto &it :planks )
		{
			it->free();
		}
		
		planks.clear();
	}
	
	red = green = blue = add = 0;
}

void Ladder::reset( int distance )
{
	while( true )
	{
		if( distance > 0 )
		{
			for( auto &it :planks )
			{
				it->x ++;
			}
			
			distance --;
		}
		else
		{
			break;
		}
	}
}



void Ladder::load( int type )
{
	free();
	
	fstream file;
	file.open( "data/txt/ladder/" +to_string( type ) +".map" );
	if( file.bad() )
	{
		printf( "Cannot load %s\n", ( "data/txt/ladder/" +to_string( type ) +".map" ).c_str() );
	}
	else
	{
		// Set color.
		int container;
		vector <int> temporary;
		while( file >> container )
		{
			temporary.push_back( container );
		}
		
		if( !temporary.empty() )
		{
			red = 	temporary[ 0 ];
			green = temporary[ 1 ];
			blue = 	temporary[ 2 ];
			
			if( temporary.size() == 4 )
			{
				add = temporary[ 3 ];
			}
			
			temporary.clear();
		}
		
		for( int i = 0; i < 2; i++ )
		{
			sprites.push_back( new MySprite() );
			sprites[ i ]->setName( "ladder[" +to_string( i ) +"]" );
			sprites[ i ]->load( "data/sprites/play/ladder/" +to_string( i ) +".png" );
		}
	}
}

void Ladder::draw( sf::RenderWindow* &window, int screen_w )
{
	for( auto &it :planks )
	{
		if( it->x > -screen_w/2 && it->x < screen_w )
		{
			sprites[ it->nr ]->setPosition( it->x, it->y );
			sprites[ it->nr ]->setColor( sf::Color( it->red, it->green, it->blue ) );
			window->draw( sprites[ it->nr ]->get() );
		}
	}
}



void Ladder::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Ladder::fadeout( int v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



int Ladder::to_int( string s )
{
	bool m = false;
    int tmp = 0;
    unsigned i = 0;
	
    if( s[ 0 ] == '-' )
    {
		i++;
		m = true;
    }
	
    while( i < s.size() )
    {
		tmp = 10*tmp +s[ i ] -48;
		i++;
    }
	
    return m ? -tmp : tmp; 
}

void Ladder::positioning( vector <Plank*> planks )
{
	this->planks = planks;
	
	for( auto &it :this->planks )
	{
		it->red = red;
		it->green = green;
		it->blue = rand()%blue +add;
	}
}




void Ladder::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :this->planks )
		{
			it->x += vel;
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :this->planks )
		{
			it->x -= vel;
		}
	}
}

void Ladder::backToGrass( int add )
{
	for( auto &it :this->planks )
	{
		it->x += add;
	}
}

bool Ladder::checkCollision( Rect* rect, int screen_w )
{
	if( rect != NULL )
	{
		for( auto &it :planks )
		{
			if( it->x > -screen_w/2 && it->x < screen_w )
			{
				sprites[ it->nr ]->setPosition( it->x, it->y );
				if( sprites[ it->nr ]->checkCollision( rect->getX() +rect->getWidth() /4, rect->getY() -50, rect->getWidth() /2, rect->getHeight() ) )
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
	return sprites[ nr ]->getWidth();
}

int Ladder::getH( sf::Uint8 nr )
{
	return sprites[ nr ]->getHeight();
}