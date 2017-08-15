#include "tiles_editor.h"
#include "own/file.h"

Tiles_editor::Tiles_editor()
{
	free();
}

Tiles_editor::~Tiles_editor()
{
	free();
}

void Tiles_editor::free()
{
	screen_w = 0;
	screen_h = 0;
	
	bg.free();
	knight.free();
	
	which = -1;
	chosen = -1;
	mouse_x = -1;
	mouse_y = -1;
	grid = true;
	width = 0;
	
	if( !tiles.empty() )
	{
		for( auto &it :tiles )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		tiles.clear();
	}
	
	if( !ws.empty() )
	{
		ws.clear();
	}
	
	if( !ns.empty() )
	{
		ns.clear();
	}
	
	if( !xs.empty() )
	{
		xs.clear();
	}
	
	if( !ys.empty() )
	{
		ys.clear();
	}
}

void Tiles_editor::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	bg.setIdentity( "tiles_editor-bg" );
	bg.load( "images/background.png" );
	bg.setScale( screen_w /2560, screen_h /1440 );
	
	knight.setIdentity( "tiles_editor-knight" );
	knight.load( "images/knight.png", 10 );
	knight.setScale( screen_w /2560, screen_h /1440 );
	
	for( unsigned i = 0; i < 16; i++ )
	{
		tiles.push_back( new MySprite() );
		tiles[ tiles.size() -1 ]->setIdentity( "tiles_editor-tiles" );
		tiles[ tiles.size() -1 ]->load( "images/tiles/" +con::itos( i ) +".png" );
		tiles[ tiles.size() -1 ]->setScale( screen_w /2560, screen_h /1440 );
	}
	
	width = tiles[ 0 ]->getWidth() /2;
}

void Tiles_editor::handle( sf::Event& event )
{
	if( event.type == sf::Event::KeyPressed )
	{
		int c = event.key.code;
		
		// g
		if( c == 6 )
		{
			grid = !grid;
		}
		
		// space // x
		else if( c == 57 || c == 23 )
		{
			chosen = 0;
		}
		
		// v
		else if( c == 21 )
		{
			chosen += 2;
		}
		
		// + || c
		else if( c == 67 || c == 2 )
		{
			chosen ++;
		}
		
		// - || z
		else if( (c == 68 || c == 25) && chosen > -1 )
		{
			chosen --;
		}
		
		// shift
		else if( c == 38 && chosen > 0 )
		{
			chosen -= 2;
		}
		
		// number 26 ... 35
		else if( c >= 26 && c <= 35 )
		{
			which = c -26;
		}
	}
	
	if( event.type == sf::Event::MouseMoved )
	{
		mouse_x = event.mouseMove.x;
		mouse_y = event.mouseMove.y;
		
		if( grid )
		{
			int count = 0;
			while( mouse_x >= width )
			{
				mouse_x -= width;
				count ++;
			}
			mouse_x = count *width;
			
			count = 0;
			int diff = static_cast <int> (screen_h) %static_cast <int> (width);
			while( mouse_y -diff >= width )
			{
				mouse_y -= width;
				count ++;
			}
			mouse_y = count *width +diff;
		}
	}
	
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			if( chosen > -1 )
			{
				ws.push_back( which );
				ns.push_back( chosen );
				xs.push_back( mouse_x );
				ys.push_back( mouse_y );
			}
			else
			{
				knight.setPosition( mouse_x -knight.getWidth() /2, mouse_y -knight.getHeight() /2 );
			}
		}
	}
}

void Tiles_editor::draw( sf::RenderWindow* &window )
{
	if( grid )	printf( "gON   " );
	else		printf( "gOFF   " );
	printf( "w:%d  c:%d   x:%f  y:%f\n", which, chosen, mouse_x, mouse_y );
	
	window->draw( bg.get() );
	window->draw( knight.get() );
	
	if( chosen > -1 )
	{
		if( which == 0 )
		{
			if( chosen < static_cast <int> (tiles.size()) )
			{
				tiles[ chosen ]->setPosition( mouse_x, mouse_y );
				window->draw( tiles[ chosen ]->get() );
			}
		}
	}
	
	for( unsigned i = 0; i < xs.size(); i++ )
	{
		if( ws[ i ] == 0 )
		{
			tiles[ ns[ i ] ]->setPosition( xs[ i ], ys[ i ] );
			window->draw( tiles[ ns[ i ] ]->get() );
		}
	}
}
