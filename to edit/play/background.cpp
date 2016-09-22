#include "background.h"

Background::Background()
{
	nr = 0;
	active = 0;
	last = 0;
	
	one = NULL;
	two = NULL;
}

Background::~Background()
{
	free();
}

void Background::free()
{
	active = 0;
	last = 0;
	
	if( one != NULL )
	{
		for( int i = 0; i < nr; i++ )
		{
			one[ i ].free();
		}
		
		delete [] one;
		one = NULL;
	}
	
	
	if( two != NULL )
	{
		for( int i = 0; i < nr; i++ )
		{
			two[ i ].free();
		}
		
		delete [] two;
		two = NULL;
	}
	
	nr = 0;
}

void Background::load( int screen_w, int screen_h )
{
	nr = 5;
	
	one = new MySprite [ nr ];
	two = new MySprite [ nr ];
	
	one[ 0 ].setAlpha( 0xFF );
	one[ 0 ].setAlpha( 0xFF );
}

void Background::draw( sf::RenderWindow* &window )
{
	window->draw( one[ last ].get() );
	window->draw( two[ last ].get() );
	
	if( active != last )
	{
		window->draw( one[ active ].get() );
		window->draw( two[ active ].get() );
		
		one[ active ].fadein( 1, 255 );
		two[ active ].fadein( 1, 255 );
	}
	
	if( one[ active ].getAlpha() == 0xFF )
	{
		last = active;
	}
}

void Background::handle( sf::Event &event )
{
	
}
	
void Background::change()
{
	active ++;
}