#pragma once

#include "drawable/sprite.h"
#include "platform/enemy/actions/expletive/slab.h"
#include "platform/world/brick/block.h"
#include <vector>
#include "saw.h"

class Saws
{
	int type;
	int width;
	int screen_w;
	
	int damage;
	float main_vel;
	
	Slab hit;
	MySprite sprite;
	vector <Saw*> saws;
	
public:
	// Basics.
	Saws();
	~Saws();
	void free();
	void reset( int distance );
	void load( int type, int screen_w, int width );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// Creating.
	void positioning( vector <Block*> b1, vector <Block*> b2, int chance );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setColor( sf::Color color );
	
	// Check collision.
	void check( Rect* rect );
	bool harm( Rect* rect );
	
	// Damage
	int getDamage();
	
	// Sound stuff.
	void turn();
	void turnOn();
	void turnOff();
	void setVolume( int v );
};