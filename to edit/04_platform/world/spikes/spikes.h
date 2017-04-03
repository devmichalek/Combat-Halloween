#pragma once

#include "drawable/sprite.h"
#include "04_platform/enemy/expletive/slab.h"
#include "04_platform/world/brick/block.h"
#include <vector>
#include "spike.h"

class Spikes
{
	int screen_w;
	int screen_h;
	
	int damage;
	float main_vel;
	MySprite sprite;
	vector <Spike*> spikes;
	Slab hit;
	
public:
	// Basics.
	Spikes();
	~Spikes();
	void free();
	void reset( int distance );
	void load( int type, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// Creating.
	void positioning( vector <Block*> blocks, int width, int chance );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setColor( sf::Color color );
	
	// Check collision.
	bool harm( Rect* rect );
	
	// Damage
	int getDamage();
	
	// Sound stuff.
	void turnOn();
	void turnOff();
	void setVolume( int v );
};