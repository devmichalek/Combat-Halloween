#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include <vector>
#include "04_platform/enemy/snakes/snakes.h"
#include "04_platform/enemy/expletive/slab.h"

class Snakes_factory
{
	enum
	{
		DELAY = 0,
		SCALE,
		DAMAGE,
		HP,
		AL,
		AMOUNT
	};
	
	
	int width;
	int screen_w;
	int screen_h;
	int damage;
	
	MyText hp;
	vector <Snakes*> snakes;
	vector <MySprite*> sprites;
	
	vector <vector <pair <int, int> >> multiplier;
	vector <float> features;
	vector <sf::Uint8> lines;
	Rect* deadRect;	// For coins.
	
	Slab hit;
	Slab stand;
	
public:
	
	// Basics.
	Snakes_factory();
	~Snakes_factory();
	void free();
	void reset( int distance );
	
	void load( int width, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// Creating.
	void addSnake( int x, int y, int chance );
	void positioning( vector <Block*> blocks, int chance );
	
	// Collision stuff.
	void appear( float x );
	bool harm( Rect* rect, int damage );
	void ableAttack(  Rect* rect );
	bool harmSomebody( Rect* rect );
	Rect* getDeadRect();
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setColor( sf::Color color );
	
	int getDamage();
	
	// Sound stuff.
	void turnOn();
	void turnOff();
	void setVolume( int v );
};