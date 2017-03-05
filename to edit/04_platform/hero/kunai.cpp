/**
    kunai.h
    Purpose: class Kunai and Bit - to contain kunai texture, throw kunai, contains max 6 kunai.

    @author Adrian Michalek
    @version 2016.12.15
	@email adrmic98@gmail.com
*/

#include "kunai.h"
#include <fstream>

Bit::Bit()
{
	x = y = 0;
	active = false;
	vel = 0;
}

Bit::~Bit()
{
	free();
}

void Bit::free()
{
	x = y = 0;
	active = false;
	vel = 0;
}



bool Bit::isActive()
{
	return active;
}

void Bit::start( int startX, int startY, int vel )
{
	if( !active )
	{
		active = true;
		this->vel = vel;
		this->x = startX;
		this->y = startY;
	}
}

void Bit::go()
{
	if( active )
	{
		x += vel;
	}
}



void Bit::destroy()
{
	active = false;
	x = y = 0;
	vel = 0;
}

	
int Bit::getX()
{
	return x;
}

int Bit::getY()
{
	return y;
}

int Bit::getVel()
{
	return vel;
}





void Kunai::throwed( int x, int y, bool right )
{
	for( unsigned i = 0; i < bits.size(); i++ )
	{
		if( !bits[ i ]->isActive() )
		{
			if( right )
			{
				bits[ i ]->start( x +30, y +50, vel );
			}
			else
			{
				bits[ i ]->start( x -30, y +50, -vel );
			}

			break;
		}
	}
}

unsigned int Kunai::getNr()
{
	return bits.size();
}



int Kunai::getX( int which )
{
	int x = bits[ which ]->getX();
	
	if( bits[ which]->getVel() > 0 )
	{
		x -= getW();
	}
	
	return x;
}

int Kunai::getW()
{
	return sprite.getWidth();
}

void Kunai::destroy( int which )
{
	bits[ which ]->destroy();
}

Rect* Kunai::getRect( int which )
{
	Rect* rect = new Rect;
	int t_x, t_y;	// temporary
	int t_w, t_h;
		
	t_x = bits[ which ]->getX();
	if( bits[ which ]->getVel() > 0 )
	{
		t_x -= sprite.getWidth();
	}
	
	t_y = bits[ which ]->getY();
	t_w = sprite.getWidth();
	t_h = sprite.getHeight();
	
	rect->set( t_x, t_y, t_w, t_h );
	return rect;
}


float Kunai::getDamage()
{
	return damage;
}



Kunai::Kunai()
{
	scale = 0;
	vel = 0;
	damage = 0;
}

Kunai::~Kunai()
{
	free();
}

void Kunai::free()
{
	sprite.free();
	
	for( unsigned i = 0; i < bits.size(); i++ )
	{
		bits[ i ]->free();
	}
	
	bits.clear();
	
	scale = 0;
	vel = 0;
	damage = 0;
}



	
void Kunai::load()
{
	scale = 0.5;
	vel = 4;
	
	sprite.setName( "kunai-sprite" );
	sprite.load( "data/04_platform/hero/shuriken/1.png" );
	
	// Max amount of kunai's is 6
	for( int i = 0; i < 6; i++ )
	{
		bits.push_back( new Bit() );
	}
	
	// damage
	fstream file;
	file.open( "data/txt/hero/kunai_current.txt" );
	if( file.bad() )
	{
		printf( "Something went wrong with data/txt/hero/kunai_current.txt\n" );
	}
	else
	{
		string line;
		file >> line;
		damage = stof( line );
	}
	file.close();
}

void Kunai::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < bits.size(); i++ )
	{
		if( bits[ i ]->isActive() )
		{
			bits[ i ]->go();
			sprite.setPosition( bits[ i ]->getX(), bits[ i ]->getY() );
			
			if( bits[ i ]->getVel() < 0 )
			{
				sprite.setScale( scale, scale );
			}
			else if( bits[ i ]->getVel() > 0 )
			{
				sprite.setScale( -scale, scale );
			}
			
			window->draw( sprite.get() );
		}
	}
}

void Kunai::fadein( int v, int max )
{
	sprite.fadein( v, max );
}

void Kunai::fadeout( int v, int min )
{
	sprite.fadein( v, min );
}