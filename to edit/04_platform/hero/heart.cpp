#include "heart.h"

Heart::Heart()
{
	nr = 0;
	fill = NULL;
	frame = NULL;
	
	flag = false;
	life = 0;
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
	life = 0;
}

	
void Heart::load()
{
	nr = 3;
	fill = new MySprite [ nr ];
	frame = new MySprite [ nr ];
	
	float scale = 0.75;
	for( int i = 0; i < nr; i++ )
	{
		fill[ i ].setName( "heart-fill[" + to_string( i ) + "]" );
		fill[ i ].load( "data/sprites/hero/heart/fill.png");
		fill[ i ].setScale( scale, scale );
		fill[ i ].setPosition( 10 + fill[ i ].getWidth()*i, 10 );
		
		frame[ i ].setName( "heart-frame[" + to_string( i ) + "]" );
		frame[ i ].load( "data/sprites/hero/heart/frame.png");
		frame[ i ].setScale( scale, scale );
		frame[ i ].setPosition( 10 + frame[ i ].getWidth()*i, 10 );
	}
	
	life = nr *0xFF;
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
		harm( -4 );
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
		
		if( frame[ 0 ].getAlpha() == 0xFF )
		{
			flag = true;
		}
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

void Heart::harm( int damage )
{
	life += damage;
	
	int temporary_life = 0;
	for( int i = 0; i < nr; i++ )
	{
		temporary_life += fill[ i ].getAlpha();
	}
	
	if( temporary_life != life )
	{
		temporary_life = life;
		
		for( int i = 0; i < nr; i++ )
		{
			fill[ i ].setAlpha( 0 );
		}
		
		if( temporary_life > 0 )
		{
			for( int i = 0; i < nr; i++ )
			{
				if( temporary_life < 0xFF )
				{
					fill[ i ].setAlpha( temporary_life );
					break;
				}
				else
				{
					fill[ i ].setAlpha( 0xFF );
				}
				
				temporary_life -= 0xFF;
			}
		}
	}
}

bool Heart::isDead()
{
	if( life <= 0 )
	{
		return true;
	}
	
	return false;
}

void Heart::reset()
{
	life = nr *0xFF;
	harm( 0 );
	flag = false;
}