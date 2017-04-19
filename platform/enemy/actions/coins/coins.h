#pragma once

#include "coin.h"
#include "platform/enemy/actions/expletive/slab.h"
#include "drawable/sprite.h"
#include <vector>

class Coins
{
	int width;
	int screen_w;
	int money;
	
	MySprite coin;
	vector <Coin*> coins;
	vector <Slab*> dropped_coins;
	vector <Slab*> jumped_coins;
	
public:
	
	Coins();
	~Coins();
	void free();
	void reset();
	
	void load( int width, int screen_w, int type );
	void setChance( int chance );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	Rect* drop( Rect* rect );
	void playDropped_coin();
	void playJumped_coin();
	
	// In action.
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setColor( sf::Color color );
	
	int getMoney();
	bool uplift( Rect* rect );
	
	// Sound stuff.
	void turn();
	void turnOn();
	void turnOff();
	void setVolume( int v );
};