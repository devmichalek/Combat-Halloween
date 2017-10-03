#pragma once
#include "own/sprite.h"
#include "own/request.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class Coins
{
	// Basics.
	float screen_w;
	float screen_h;
	float border_x;
	float border_y;
	
	int line;
	int width;
	float offset;
	MySprite sprite;
	vector <vector <bool>> tiles;
	
	// Thread stuff.
	string error;
	MyThread thread;
	
public:
	
	// Basics.
	Coins();
	~Coins();
	void free();
	void reset();
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Thread.
	bool isNull();
	bool isReady();
	void setThread( string message );
	void prepare( string message );
	string getError();
	
	// Borders.
	void setBorderX( float x );
	void setBorderY( float y );
};