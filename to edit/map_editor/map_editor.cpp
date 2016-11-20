#include "map_editor/map_editor.h"


Map_editor::Map_editor()
{
	state = 0;
	ch_m = NULL;
	palette = NULL;
	
	w = h = 0;
}

Map_editor::~Map_editor()
{
	state = 0;
	delete ch_m;
	delete palette;
	w = h = 0;
}


void Map_editor::load( int screen_w, int screen_h )
{
	ch_m = new Choose_map;
	ch_m->load( screen_w );
	
	palette = new Palette;
	w = screen_w;
	h = screen_h;
}

void Map_editor::draw( sf::RenderWindow* &window )
{
	if( state == 0 )
	{
		ch_m->draw( window );
		
		if( ch_m->chosenMap() != -1 )
		{
			state = 1;
			palette->load( w, h, ch_m->chosenMap() );
		}
	}
	
	if( state == 1 )
	{
		palette->draw( window );
	}
}

void Map_editor::handle( sf::Event &event )
{
	if( state == 0 )
	{
		ch_m->handle( event );
	}
	
	if( state == 1 )
	{
		
	}
}
