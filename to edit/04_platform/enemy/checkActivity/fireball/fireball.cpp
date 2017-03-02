#include "04_platform/enemy/checkActivity/fireball/fireball.h"

Fireball::Fireball()
{
	delay = 0;
	line = 0;
	counter_line = 0;
	fps = 0;
	screen_w = 0;
	reset();
}

Fireball::~Fireball()
{
	free();
}

void Fireball::free()
{
	if( !sprite.empty() )
	{
		for( auto &it :sprite )
		{
			it->free();
		}
		
		sprite.clear();
	}
	
	delay = 0;
	counter_line = 0;
	fps = 0;
	reset();
}

void Fireball::reset()
{
	offset = 0;
	state = 0;
	counter = 0;
	counter_line = 20 *fps;
	which = 0;
}



void Fireball::load( int fps, int screen_w )
{
	this->screen_w = screen_w;
	line = 5;
	int nr = 2;
	
	for( int i = 0; i < nr; i++ )
	{
		sprite.push_back( new MySprite() );
		sprite[ sprite.size() -1 ]->setName( "fireball-sprite" );
	}
	
	sprite[ 0 ]->load( "data/04_platform/enemy/fireball/0.png", line );
	sprite[ 1 ]->load( "data/04_platform/enemy/fireball/1.png", line +1 );
	
	
	delay = 10;
	this->fps = fps;
	reset();
}

void Fireball::draw( sf::RenderWindow* &window )
{
	if( state > 0 )
	{
		// printf( "%d\n", which );
		sprite[ which ]->setOffset( offset /delay );
		window->draw( sprite[ which ]->get() );
	}
}

void Fireball::fadein( int v, int max )
{
	for( auto &it :sprite )
	{
		it->fadein( v, max /2 );
	}
}

void Fireball::fadeout( int v, int min )
{
	for( auto &it :sprite )
	{
		it->fadeout( v, min );
	}
}



void Fireball::moveX( sf::Uint8 direction, float vel )
{
	if( state > 0 )
	{
		if( direction == 1 )
		{
			for( auto &it :sprite )
			{
				it->setPosition( it->getX() +vel, it->getY() );
			}
		}
		else if( direction == 2 )
		{
			for( auto &it :sprite )
			{
				it->setPosition( it->getX() -vel, it->getY() );
			}
		}
	}
}

void Fireball::undoFall( sf::Uint8 add )
{
	for( auto &it :sprite )
	{
		it->setPosition( it->getX() +add, it->getY() );
	}
}

void Fireball::mechanics( int y, sf::Uint8 direction )
{
	if( direction != 0 )
	{
		counter = 0;
	}
	
	if( state == 0 )
	{
		which = 0;
		counter ++;
		if( counter >= counter_line )
		{
			for( auto &it :sprite )
			{
				it->setPosition( screen_w, y -it->getHeight()/2 );
			}
			counter = 0;
			state = 1;
			offset = 0;
		}
	}
	
	else if( state > 0 )
	{
		if( which == 0 )
		{
			offset ++;
			if( offset == line *delay )
			{
				offset = 0;
			}
		}
		else if( which == 1 )
		{
			offset ++;
			if( offset == (line +1) *delay )
			{
				state = 0;
				offset = 0;
			}
		}
		
		for( auto &it :sprite )
		{
			it->setPosition( it->getX() -2, it->getY() );
		}
		
		if( sprite[ 0 ]->getX() +sprite[ 0 ]->getWidth() < 0 )
		{
			state = 0;
			offset = 0;
		}
		// printf( "%d %d\n", sprite[ 0 ]->getX(), sprite[ 0 ]->getY() );
	}
}

bool Fireball::harmSomebody( Rect* rect )
{
	if( rect != NULL && state > 0 )
	{
		if( rect->checkCollision( sprite[ which ]->getX(), sprite[ which ]->getY(), sprite[ which ]->getWidth(), sprite[ which ]->getHeight() ) )
		{
			if( which == 0 )
			{
				offset = 0;
				which = 1;
			}
			
			return true;
		}
	}
	
	return false;
}

int Fireball::getDamage()
{
	return 0xFF;
}

bool Fireball::harmed()
{
	if( offset == 1 *delay && which == 1 )
	{
		return true;
	}
	
	return false;
}