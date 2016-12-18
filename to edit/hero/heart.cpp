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
	nr = 3;
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

void Heart::harm( float damage )
{
	for( int i = nr-1; i >= 0; i-- )
	{
		if( fill[ i ].getAlpha() > 0 )
		{
			if( fill[ i ].getAlpha() -damage*10 < 0 )
				fill[ i ].setAlpha( 0 );
			else
				fill[ i ].setAlpha( fill[ i ].getAlpha() -damage*10 );
			break;
		}
	}
}