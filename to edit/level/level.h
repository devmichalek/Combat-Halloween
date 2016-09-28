#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "menu/parentchunk.h"

class Level :public Parentchunk
{
	int cost;
	string name;
	
	sf::Uint8 state;

	
	MySprite one;
	MySprite two;
	
	Chunk lock;	// sound
	Chunk unlocking;
	
public:
	
	Level();
	~Level();
	
	void load( string name, int cost );
	void setXY( int x, int y );
	
	void draw( sf::RenderWindow* &window );
	sf::Uint8 handle( sf::Event &event, int& money );	// unlock during drawing

	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	int getCost();
	string getName();
	
	void unlock(); // before draw
	bool isReady();
	
	int getWidth();
	int getHeight();
	int getX();
	int getY();
	
	void setVolume( sf::Uint8 volume );
};