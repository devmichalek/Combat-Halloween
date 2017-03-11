#pragma once

#include "drawable/sprite.h"
#include <cstdint>

class Rain_cloud
{
protected:
	
	float x;
	float vel;
	MySprite cloud;
	vector <int16_t> alphas;
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
	
	void setCloud( int screen_w );
	void setVel();
};