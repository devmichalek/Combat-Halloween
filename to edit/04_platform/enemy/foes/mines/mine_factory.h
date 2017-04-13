#pragma once

#include "drawable/sprite.h"
#include <vector>
#include "mine.h"
#include "04_platform/enemy/actions/expletive/slab.h"

class Mine_factory
{
	int width;
	int screen_w;
	int screen_h;
	int damage;
	sf::Uint8 type;
	
	vector <Mine*> mines;
	vector <MySprite*> sprites;
	Slab ticktock;
	Slab explosion;
	Slab plush;
	
public:
	
	// Basics.
	Mine_factory();
	~Mine_factory();
	void free();
	void reset( int distance );
	
	void load( int type, int width, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// Creating.
	void addMine( int x1, int x2, int y );
	void positioning( vector <Block*> blocks, int chance );
	
	// Collision.
	void checkCollision( Rect* rect );
	bool harm( Rect* rect );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setColor( sf::Color color );
	
	int getDamage();
	
	// Sound stuff.
	void turn();
	void turnOn();
	void turnOff();
	void setVolume( int v );
};