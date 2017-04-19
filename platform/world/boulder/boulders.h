#pragma once

#include "drawable/sprite.h"
#include "platform/enemy/actions/expletive/slab.h"
#include "boulder.h"

class Boulder
{
	int width;
	int screen_w;
	int damage;
	
	vector <Boulder_part*> blocks;
	vector <MySprite*> sprites;
	Slab hit;
	Slab plush;
	
	float main_vel;
	float main_angle;
	
public:
	
	// Basics.
	Boulder();
	~Boulder();
	void free();
	void reset( int distance );
	void load( int type, int width, int screen_w );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	
	// Creating.
	void positioning( vector <Block*> blocks, vector <int> xs, int chance );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics( Rect* rect );
	void setColor( sf::Color color );
	
	// Check collision.
	bool harm( Rect* rect );
	
	// Damage
	int getDamage();
	
	// Sound stuff.
	void turn();
	void turnOn();
	void turnOff();
	void setVolume( int v );
};