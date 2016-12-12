#include "hero/heart.h"

Heart::Heart()
{
	nr = 0;
	fill = NULL;
	frame = NULL;
	
	flag = false;
}

Heart::~Heart()
{
	free();
}

void Heart::free()
{
	if( fill != NULL )
	{
		for( int i = 0; i < nr; i++ )
		{
			fill[ i ].free();
		}
		
		delete [] fill;
		fill = NULL;
	}
	
	if( frame != NULL )
	{
		for( int i = 0; i < nr; i++ )
		{
			frame[ i ].free();
		}
		
		delete [] frame;
		frame = NULL;
	}
	
	nr = 0;
	flag = false;
}

	
void Heart::load()
{
	nr = 4;
	fill = new MySprite [ nr ];
	frame = new MySprite [ nr ];
	
	for( int i = 0; i < nr; i++ )
	{
		fill[ i ].setName( "heart-fill[" + to_string( i ) + "]" );
		fill[ i ].load( "data/sprites/hero/heart/fill.png");
		fill[ i ].setScale( 0.75, 0.75 );
		fill[ i ].setPosition( 10 + fill[ i ].getWidth()*i, 10 );
		
		frame[ i ].setName( "heart-frame[" + to_string( i ) + "]" );
		frame[ i ].load( "data/sprites/hero/heart/frame.png");
		frame[ i ].setScale( 0.75, 0.75 );
		frame[ i ].setPosition( 10 + frame[ i ].getWidth()*i, 10 );
	}
}

void Heart::draw( sf::RenderWindow* &window )
{
	for( int i = 0; i < nr; i++ )
	{
		window->draw( fill[ i ].get() );
		window->draw( frame[ i ].get() );
	}
	
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 0 ) ) )
	{
		for( int i = nr-1; i >= 0; i-- )
		{
			if( fill[ i ].getAlpha() > 0 )
			{
				fill[ i ].setAlpha( fill[ i ].getAlpha() -1 );
				break;
			}
		}
	}
	
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 3 ) ) )
	{
		for( int i = 0; i < nr; i++ )
		{
			if( fill[ i ].getAlpha() < 0xFF )
			{
				fill[ i ].setAlpha( fill[ i ].getAlpha() +1 );
				break;
			}
		}
	}
}

void Heart::fadein( int v, int max )
{
	if( !flag )
	{
		for( int i = 0; i < nr; i++ )
		{
			fill[ i ].fadein( v, max );
			frame[ i ].fadein( v, max );
		}
		
		if( fill[ 0 ].getAlpha() == 0xFF )
			flag = true;
	}
}

void Heart::fadeout( int v, int min )
{
	for( int i = 0; i < nr; i++ )
	{
		fill[ i ].fadeout( v, min );
		frame[ i ].fadeout( v, min );
	}
}
