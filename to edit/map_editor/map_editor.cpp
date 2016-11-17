#include "map_editor/map_editor.h"


Map_editor::Map_editor()
{
	ch_m = NULL;
}

Map_editor::~Map_editor()
{
	delete ch_m;
}


void Map_editor::load( int screen_w, int screen_h )
{
	ch_m = new Choose_map;
	ch_m->load( screen_w );
}

void Map_editor::draw( sf::RenderWindow* &window )
{
	ch_m->draw( window );
}

void Map_editor::handle( sf::Event &event )
{
	ch_m->handle( event );
}
