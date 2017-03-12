#pragma once

#include "04_platform/world/weather/snow/snow_cloud.h"
#include <vector>

class Snow
{
	int screen_w;
	int screen_h;
	
	vector <Snow_cloud*> clouds;
	
public:
	
	Snow();
	~Snow();
	void free();
	void reset();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	void mechanics();
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
};