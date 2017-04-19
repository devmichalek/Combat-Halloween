#pragma once

#include "drawable/sprite.h"

class Fly
{
	float x, y;
	int screen_w;
	int screen_h;
	
	MySprite sprite;
	
	int offset;
	sf::Uint8 delay;
	int line;
	
	sf::Uint8 alpha;
	bool alpha_state;
	sf::Uint8 state;
	
	sf::Uint8 direction;
	
	float vel;
	float scale;
	
	int counter;
	int counter_line;
	
	sf::Uint8 floor;
	sf::Uint8 floor_state;
	
public:
	
	Fly();
	~Fly();
	void free();
	void reset();
	
	void load( int screen_w, int screen_h, string path );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int j = 1, int max = 0xFF );
	void fadeout( int j = 1, int min = 0 );
	
	// In action
	void moveX( sf::Uint8 d, float v );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setColor( sf::Color color );
};