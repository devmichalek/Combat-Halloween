#pragma once

#include "map_editor/choose_map.h"
#include "map_editor/palette.h"
#include "map_editor/saveLog.h"
#include "map_editor/brickXY.h"

class Map_editor
{
	int state;
	int w, h;
	
	Choose_map* ch_m;
	Palette* palette;
	SaveLog* saveLog;
	BrickXY* brickXY;
	
public:
	
	Map_editor();
    ~Map_editor();

    void load( int screen_w, int screen_h );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
};