#pragma once

#include "drawable/sprite.h"
#include "04_platform/enemy/expletive/slab.h"
#include "pug.h"

class Wall
{
	int width;
	int screen_w;
	int damage;
	
	vector <Pug*> blocks;
	vector <MySprite*> sprites;
	Slab hit;
	
public:
	
	// Basics.
	Wall();
	~Wall();
	void free();
	void reset( int distance );
	void load( int type, int width, int screen_w );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	
	// Creating
	void positioning( vector <Block*> blocks, int chance );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setColor( sf::Color color );
	
	// Check collision.
	bool harm( Rect* rect );
	bool checkCollision( Rect* rect );
	
	// Damage
	int getDamage();
	int getFallDamage();
	
	// Sound stuff.
	void turnOn();
	void turnOff();
	void setVolume( int v );
	
	// For boulder.
	vector <int> getXs();
};