#pragma once

#include "drawable/sprite.h"

class Rain_cloud
{
	MySprite cloud;
	vector <sf::ConvexShape*> drops;
	
public:
	
	Rain_cloud();
	~Rain_cloud();
	void free();
	void reset( int screen_w, int screen_h );
	
	void create( string path, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	void mechanics( int screen_w, int screen_h );
	void moveX( int add );
	
	int getX();
	int getWidth();
};