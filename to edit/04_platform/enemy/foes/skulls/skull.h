#pragma once

#include "drawable/sprite.h"

class Skull
{
	int screen_w;
	int screen_h;
	
	MySprite sprite;
	
	float x, y;
	float startX, endX;
	float g_x, g_y;	// our goal
	
	double angle;
	
	int line;
	int offset;
	sf::Uint8 delay;
	
	sf::Uint8 alpha;
	bool alpha_state;
	sf::Uint8 state;
	
	float vel;
	float scale;
	
	int counter;
	int counter_line;
	sf::Uint8 direction;
	
public:
	
	Skull();
	~Skull();
	void free();
	void reset();
	
	void load( int screen_w, int screen_h, string path );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int j = 1, int max = 0xFF );
	void fadeout( int j = 1, int min = 0 );
	
	// In action
	void moveX( sf::Uint8 d, float v );
	void undoFall( sf::Uint8 add );
	void mechanics( int x, int y );
	void setColor( sf::Color color );
};