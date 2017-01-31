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
		for( unsigned i = 0; i < sprites.size(); i++ )
		{
			sprites[ i ]->free();
		}
		
		sprites.clear();
	}
	
	if( !planks.empty() )
	{
		for( unsigned i = 0; i < planks.size(); i++ )
		{
			planks[ i ]->free();
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
			for( unsigned i = 0; i < planks.size(); i++ )
			{
				planks[ i ]->x += 1;
			}
			
			distance -= 1;
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
			sprites[ i ]->loadByImage( "data/sprites/play/ladder/" +to_string( i ) +".png" );
		}
	}
}

void Ladder::draw( sf::RenderWindow* &window, int screen_w )
{
	for( unsigned i = 0; i < planks.size(); i++ )
	{
		if( planks[ i ]->x > -screen_w/2 && planks[ i ]->x < screen_w )
		{
			sprites[ planks[ i ]->nr ]->setPosition( planks[ i ]->x, planks[ i ]->y );
			sprites[ planks[ i ]->nr ]->setColor( sf::Color( planks[ i ]->red, planks[ i ]->green, planks[ i ]->blue ) );
			window->draw( sprites[ planks[ i ]->nr ]->get() );
		}
	}
}

void Ladder::fadein( int v, int max )
{
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		sprites[ i ]->fadein( v, max );
	}
}

void Ladder::fadeout( int v, int min )
{
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		sprites[ i ]->fadeout( v, min );
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
	
	for( unsigned i = 0; i < this->planks.size(); i++ )
	{
		this->planks[ i ]->red = red;
		this->planks[ i ]->green = green;
		this->planks[ i ]->blue = rand()%blue +add;
	}
}




void Ladder::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( unsigned i = 0; i < planks.size(); i++ )
		{
			planks[ i ]->x += vel;
		}
	}
	else if( direction == 2 )
	{
		for( unsigned i = 0; i < planks.size(); i++ )
		{
			planks[ i ]->x -= vel;
		}
	}
}

void Ladder::backToGrass( int add )
{
	for( unsigned i = 0; i < planks.size(); i++ )
	{
		planks[ i ]->x += add;
	}
}

bool Ladder::checkCollision( Rect* rect, int screen_w )
{
	if( rect != NULL )
	{
		for( unsigned i = 0; i < planks.size(); i++ )
		{
			if( planks[ i ]->x > -screen_w/2 && planks[ i ]->x < screen_w )
			{
				sprites[ planks[ i ]->nr ]->setPosition( planks[ i ]->x, planks[ i ]->y );
				if( sprites[ planks[ i ]->nr ]->checkCollision( rect->getX() +rect->getWidth() /4, rect->getY() -50, rect->getWidth() /2, rect->getHeight() ) )
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