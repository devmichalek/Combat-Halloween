#pragma once

#include "map_editor/choose_map.h"

class Map_editor
{
	int state;
	Choose_map* ch_m;
	
public:
	
	Map_editor();
    ~Map_editor();

    void load( int screen_w, int screen_h );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
};