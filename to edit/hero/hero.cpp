#include "hero/hero.h"

Hero::Hero()
{
	which = 0;
	offset = 0;
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

	
void Hero::load( int screen_w, int screen_h )
{
	free();
	//printf( "--%d--\n", off_const );
	
	nr = 11;
	sprite = new MySprite [ nr ];
	
	// set name
	for( int i = 0; i < nr; i++ )
		sprite[ i ].setName( "hero-sprite nr " + to_string( i ) );
		
	// load texture
	sprite[ 0 ].load( "data/sprites/hero/idle.png", off_const );
}

void Hero::draw( sf::RenderWindow* &window )
{
	
}

void Hero::handle( sf::Event &event )
{
	
}
