#include "hero/hero.h"

Hero::Hero()
{
	which = 0;
	offset = 0;
	delay = 0;
	nr = 0;
	sprite = NULL;
	
	int &wr = const_cast <int&> ( off_const ); 
	wr = 10;
}

Hero::~Hero()
{
	free();
}

void Hero::free()
{
	which = 0;
	offset = 0;
	delay = 0;
	
	if( sprite != NULL )
	{
		for( int i = 0; i < nr; i ++ )
		{
			sprite[ i ].free();
		}
		
		delete [] sprite;
		sprite = NULL;
		nr = 0;
	}
}

	
void Hero::load( int screen_w, int y )
{
	free();
	//printf( "--%d--\n", off_const );
	delay = 3;
	
	nr = 11;
	sprite = new MySprite [ nr ];
	
	// set name
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setName( "hero-sprite nr " + to_string( i ) );
		sprite[ i ].load( "data/sprites/hero/0/" + to_string( i ) + ".png", off_const );
		sprite[ i ].setScale( 0.25, 0.25 );
		sprite[ i ].setPosition( 10 + 90*i, y -sprite[ i ].getHeight() -124 );
	}
}

void Hero::draw( sf::RenderWindow* &window )
{
	for( int i = 0; i < nr; i++ )
	{
		window->draw( sprite[ i ].get() );
		sprite[ i ].setOffset( offset /delay );
	}
	
	offset ++;
	if( offset == off_const *delay )
		offset = 0;
}

void Hero::handle( sf::Event &event )
{
	
}




void Hero::fadein( int v, int max )
{
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].fadein( v, max );
	}
}

void Hero::fadeout( int v, int min )
{
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].fadeout( v, min );
	}
}
