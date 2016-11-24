#include "map_editor/palette.h"

#define width 128

Palette::Palette()
{
	folder_name = "";
	nr = 0;
	block = NULL;
	
	which = -1;
	x = -1;
	y = -1;
}

Palette::~Palette()
{
	free();
}

void Palette::free()
{
	if( block != NULL )
	{
		delete [] block;
		block = NULL;
		nr = 0;
	}
	
	folder_name = "";
	bar.free();
	
	which = -1;
	x = -1;
	y = -1;
}


void Palette::load( int screen_w, int screen_h, int num )
{
	bar.setName( "palette-bar" );
	bar.create( width, screen_h );
	bar.setColor( sf::Color( 0xCC, 0xCC, 0xCC ) );
	bar.setAlpha( 0xFF );
	
	if( num == 0 )		nr = 30;
	else if( num == 1 )	nr = 31;
	else if( num == 2 )	nr = 28;
	else				nr = 30;
	
	
	block = new MySprite[ nr ];
	
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].setName( "palette-block[" +to_string( i ) +"]" );
		block[ i ].load( "data/sprites/play/" +to_string( num ) +"/" +to_string( i ) +".png" );
		block[ i ].setAlpha( 100 );
	}
	
	// set first line
	block[ 0 ].setPosition( screen_w -block[ 0 ].getWidth(), 0 );
	for( int i = 5; i < nr; i += 5 )
	{
		block[ i ].setPosition( block[ i -5 ].getX() - block[ i -5 ].getWidth() -5, block[ 0 ].getY() );
	}
	
	// set other lines
	for( int j = 1; j < nr; j += 5 )
	{
		for( int i = j; i < j + 4; i++ )
		{
			if( i == nr  )
				break;
			block[ i ].setPosition( block[ j -1 ].getX(), block[ i -1 ].getBot() +5 );
		}
	}
}

void Palette::draw( sf::RenderWindow* &window )
{
	window->draw( bar.get() );
	   
	for( int i = 0; i < nr; i ++ )
	{
		window->draw( block[ i ].get() );
	}
	
	if( which != -1 )
	{
		int tx = block[ which ].getX();
		int ty = block[ which ].getY();
		
		block[ which ].center( x, y, 0, 0 );
		window->draw( block[ which ].get() );
		block[ which ].setPosition( tx, ty );
	}
}

void Palette::handle( sf::Event &event )
{
	int mx, my;

	for( int i = 0; i < nr; i ++ )
	{
		block[ i ].setAlpha( 100 );
	}
	bar.setColor( sf::Color( 0xCC, 0xCC, 0xCC ) );

	if( event.type == sf::Event::MouseMoved )
	{
		x = mx = event.mouseMove.x;
		y = my = event.mouseMove.y;
		
		for( int i = 0; i < nr; i ++ )
		{
			if( block[ i ].checkCollision( mx, my ) )
			{
				block[ i ].setAlpha( 150 );
				break;
			}
		}
		
		if( bar.checkCollision( mx, my ) )
		{
			bar.setColor( sf::Color( 0xCC, 0xCC, 88 ) );
		}
	}

	if( event.type == sf::Event::MouseButtonPressed )
	{
		x = mx = event.mouseButton.x;
		y = my = event.mouseButton.y;
			
		for( int i = 0; i < nr; i ++ )
		{
			if( block[ i ].checkCollision( mx, my ) )
			{
				which = i;
				break;
			}
		}
	}
}
