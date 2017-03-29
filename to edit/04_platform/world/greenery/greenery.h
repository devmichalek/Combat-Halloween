#pragma once

#include "plant.h"
#include "green.h"
#include "drawable/sprite.h"

class Greenery
{
	int width;
	int screen_w;
	sf::Uint8 min;
	
	vector <Plant*> plants;
	vector <Green*> blocks;
	vector <MySprite*> sprites;
	
public:
	
	// Basics.
	Greenery();
	~Greenery();
	void free();
	void reset( int distance );
	
	void load( int type, int width, int screen_w );
	void draw( sf::RenderWindow* &window );
	void draw_bg( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	
	// Creating
	unsigned getDistance( int v1, int v2 );
	void positioning( vector <Block*> blocks );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void setColor( sf::Color color );
};