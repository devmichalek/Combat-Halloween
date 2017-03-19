#pragma once

#include "04_platform/world/weather/rain/rain_cloud.h"

class Snow_cloud :public Rain_cloud
{
	vector <sf::CircleShape*> drops;
	
public:
	
	using Rain_cloud::Rain_cloud;
	
	void free();
	void reset( int screen_w, int screen_h );
	
	void draw( sf::RenderWindow* &window );
	void fadeout( int v, int min );
	
	void create( string path, int screen_w, int screen_h );
	void mechanics( int screen_w, int screen_h );
	
	void moveX( int add );
};