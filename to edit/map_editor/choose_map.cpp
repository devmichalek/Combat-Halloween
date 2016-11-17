#include "map_editor/choose_map.h"

Choose_map::Choose_map()
{
	state = 0;
	nr = 0;
	sprite = NULL;
}

Choose_map::~Choose_map()
{
	free();
}

void Choose_map::free()
{
	state = 0;
	
	if( sprite != NULL )
	{
		delete [] sprite;
		nr = 0;
	}
	
	text.free();
}

void Choose_map::load( int screen_w )
{
	free();
	
	nr = 4;
	sprite = new MySprite [ nr ];
	
	register int sum = 0;
	
	for( int i = 0; i < nr; i ++ )
	{
		sprite[ i ].setName( "choose_map[" + to_string( i ) + "]" );
		sprite[ i ].load( "data/sprites/level/" + to_string( i ) + ".png" );
		sprite[ i ].setScale( 0.2, 0.2 );
		sum += sprite[ i ].getWidth() +20;
		sprite[ i ].setAlpha( 255 );
	}
	
	sprite[ 0 ].setPosition( screen_w/2 - sum/2, 350 );
	sprite[ 1 ].setPosition( sprite[ 0 ].getRight() + 15, 350 );
	sprite[ 2 ].setPosition( sprite[ 1 ].getRight() + 15, 350 );
	sprite[ 3 ].setPosition( sprite[ 2 ].getRight() + 15, 350 );
	
	
	text.setID( "choose_map -text" );
	text.setFont( "data/fonts/Jaapokki-Regular.otf", 44, 255, 255, 255 );
	text.setText( "Edit mode, choose map to add rule" );
	text.setPosition( screen_w/2 - text.getWidth()/2, 250 );
	text.setAlpha( 255 );
}

void Choose_map::draw( sf::RenderWindow* &window )
{
	for( int i = 0; i < nr; i++ )
	{
		window->draw( sprite[ i ].get() );
	}
	
	window->draw( text.get() );
}

void Choose_map::handle( sf::Event &event )
{
	
}
