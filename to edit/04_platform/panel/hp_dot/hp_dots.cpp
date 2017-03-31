#include "04_platform/panel/hp_dot/hp_dots.h"
#include <cstdlib>
#include "file/file.h"


Hp_dots::Hp_dots()
{
	free();
}

Hp_dots::~Hp_dots()
{
	free();
}

void Hp_dots::free()
{
	hp = 0;
	screen_w = 0;
	main_alpha = 0;
	if( !dots.empty() )
	{
		for( auto &it :dots )
		{
			delete it;
		}
		
		dots.clear();
	}
}

void Hp_dots::reset()
{
	for( auto &it :dots )
	{
		it->active = false;
	}
}



void Hp_dots::load( int type, int screen_w )
{
	free();
	
	this->screen_w = screen_w;
	
	MyFile file;
	file.load( "data/txt/hp_dots/settings.txt" );
	if( file.is_good() )
	{
		int c = type;
		string line;
		while( file.get() >> line )
		{
			if( c == 0 )
			{
				hp = con::stoi( line );
				break;
			}
			
			c--;
		}
	}
	file.free();
	
	unsigned size = 30;
	for( unsigned i = 0; i < size; i++ )
	{
		dots.push_back( new Hp_dot() );
		dots[ dots.size() -1 ]->radius = static_cast <float> (rand()%150) /10;
		dots[ dots.size() -1 ]->alpha = rand()%(0xFF /2) +(0xFF /2);
	}
}

void Hp_dots::draw( sf::RenderWindow* &window )
{
	for( auto &it :dots )
	{
		if( it->active )
		{
			// Set scale.
			shape.setRadius( it->radius );
			shape.setPointCount( 4 );
			
			// Set XY.
			shape.setPosition( it->x, it->y );
			
			// Set alpha.
			shape.setFillColor( sf::Color( 0xD6, 0x3E, 0x59, main_alpha /it->alpha *0xFF ) );
			
			// Draw.
			window->draw( shape );
		}
	}
}



void Hp_dots::fadein( int v, int max )
{
	if( main_alpha +v <= max )
	{
		main_alpha += v;
	}
}

void Hp_dots::fadeout( int v, int min )
{
	if( main_alpha -v >= min )
	{
		main_alpha -= v;
	}
}



void Hp_dots::moveX( sf::Uint8 d, float v )
{
	if( d == 1 )
	{
		for( auto &it :dots )
		{
			it->x += v;
		}
	}
	else if( d == 2 )
	{
		for( auto &it :dots )
		{
			it->x -= v;
		}
	}
	
}

void Hp_dots::undoFall( sf::Uint8 add )
{
	for( auto &it :dots )
	{
		it->x += add;
	}
}

void Hp_dots::mechanics()
{
	for( auto &it :dots )
	{
		if( it->x < 0 || it->x > screen_w )
		{
			it->active = false;
		}
	}
}

void Hp_dots::setAlpha( int alpha )
{
	main_alpha = alpha;
}



void Hp_dots::drop( Rect* rect )
{
	if( rect != NULL )
	{
		int c = rand() %2 + 5;
	
		for( auto &it :dots )
		{
			if( c == 0 )	break;
			
			if( !it->active )
			{
				c --;
				it->active = true;
				it->x = rect->getX() +rand()%40;
				it->y = rect->getY() +rand()%30 -90;
			}
		}
	}
}

bool Hp_dots::uplift( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :dots )
		{
			if( it->active )
			{
				if( rect->getY() +rect->getHeight() <= it->y )
					continue;

				if( rect->getY() >= it->y + shape.getRadius() )
					continue;

				if( rect->getX() + rect->getWidth() <= it->x )
					continue;

				if( rect->getX() >= it->x + shape.getRadius() )
					continue;
				
				it->active = false;
				return true;
			}
		}
	}
	
	return false;
}

int Hp_dots::getHP()
{
	return hp;
}