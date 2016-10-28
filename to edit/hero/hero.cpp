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

	
void Hero::load( int& screen_w, int& y, string path )
{
	free();
	//printf( "--%d--\n", off_const );
	delay = 3;
	
	nr = DEAD +1;
	sprite = new MySprite [ nr ];
	
	// set name, load, set scale, set start position
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setName( "hero-sprite nr " + to_string( i ) );
		sprite[ i ].load( path + to_string( i ) + ".png", off_const );
		sprite[ i ].setScale( 0.25, 0.25 );
		sprite[ i ].setPosition( 10 + 90*i, y -sprite[ i ].getHeight() -124 );
	}
}

void Hero::draw( sf::RenderWindow* &window )
{
	window->draw( sprite[ which ].get() );
	sprite[ which ].setOffset( offset /delay );
	
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
