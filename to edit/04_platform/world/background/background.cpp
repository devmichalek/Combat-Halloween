#include "background.h"
#include "file/file.h"

Background::Background()
{
	screen_w = 0;
	screen_h = 0;
}

Background::~Background()
{
	free();
}

void Background::free()
{
	screen_w = 0;
	screen_h = 0;
	
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
}

void Background::reset( int x, int y )
{
	setPosition( x, y );
}



void Background::load( int type, int screen_w, int screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	if( type == 1 )
	{
		for( unsigned i = 0; i < 2; i++ )
		{
			sprites.push_back( new MySprite() );
			sprites[ sprites.size() -1 ]->setName( "background-sprite" );
			sprites[ sprites.size() -1 ]->load( "data/04_platform/world/1/bg" +con::itos( i ) +".png" );
		}
	}
	else
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setName( "background-sprite" );
		sprites[ sprites.size() -1 ]->load( "data/04_platform/world/" +con::itos( type ) +"/bg.png" );
	}
}

void Background::draw( sf::RenderWindow* &window )
{
	window->draw( sprites[ 0 ]->get() );
}

void Background::drawFront( sf::RenderWindow* &window )
{
	window->draw( sprites[ sprites.size() -1 ]->get() );
}


void Background::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Background::fadeout( int v, int min )
{
	if( sprites.size() > 1 )
	{
		sprites[ sprites.size() -1 ]->setAlpha( min );
	}
	
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



void Background::setPosition( int x, int y )
{
	float new_x = -( screen_w/2 ) *x /screen_w;
	float new_y = -150 *( y +300 ) /screen_h;
	
	for( auto &it :sprites )
	{
		if( new_y > -( it->getHeight() -screen_h ) && new_y < 0 )
		{
			it->setPosition( new_x, new_y );
		}
	}
}

sf::Uint8 Background::getAlpha()
{
	return sprites[ 0 ]->getAlpha();
}

void Background::setColor( sf::Color color )
{
	for( auto &it :sprites )
	{
		it->setColor( color );
	}
}



int Background::getX()
{
	return sprites[ 0 ]->getX() +sprites[ 0 ]->getWidth() /2;
}

int Background::getY()
{
	return sprites[ 0 ]->getY() +sprites[ 0 ]->getHeight();
}