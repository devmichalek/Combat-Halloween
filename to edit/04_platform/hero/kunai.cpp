#include "kunai.h"



void Kunai::throwed( int x, int y, bool right )
{
	for( unsigned i = 0; i < bits.size(); i++ )
	{
		if( !bits[ i ]->isActive() )
		{
			if( right )		bits[ i ]->start( x +30, y +50, vel );
			else			bits[ i ]->start( x -30, y +50, -vel );

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
		x -= getW();
	
	return x;
}

int Kunai::getY( int which )
{
	return bits[ which ]->getY();
}

int Kunai::getW()
{
	return sprite.getWidth();
}

int Kunai::getH()
{
	return sprite.getHeight();
}

int Kunai::getR( int which )
{
	return bits[ which ]->getX();
}

int Kunai::getB( int which )
{
	return bits[ which ]->getY() + getH();
}

void Kunai::destroy( int which )
{
	bits[ which ]->destroy();
}

/*
bool Kunai::allow()
{
	bool flag = false;
	
	for( unsigned i = 0; i < bits.size(); i++ )
	{
		if( !bits[ i ]->isActive() )
		{
			flag = true;
			break;
		}
	}
	
	return flag;
}
*/

Rect* Kunai::getRect( int which )
{
	Rect* rect = new Rect;
	int t_x, t_y;	// temporary
	int t_w, t_h;
		
	t_x = bits[ which ]->getX();
	if( bits[ which ]->getVel() > 0 )
		t_x -= sprite.getWidth();
	
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
	scale = 1;
	vel = 4;
	damage = 0.03;
	
	sprite.setName( "kunai-sprite" );
	sprite.load( "data/sprites/hero/0.png" );
	
	// Max amount of kunai's is 6
	for( int i = 0; i < 6; i++ )
	{
		bits.push_back( new Bit() );
	}
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