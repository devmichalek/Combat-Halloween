#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "templates/chunk.h"

class Level
{
	int cost;
	int name;
	bool clicked;
	bool locked;
	
	// focus on button true/false
	bool focus;
	
	MySprite sprite;
	
	// click as sound and play as state
	bool play;
	Chunk click;
	
public:
	
	Level();
	~Level();
	
	void load( int name, int cost );
	void setXY( int x, int y );
	
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event, int& money );
	
	void buy( int& money );
	int getName();
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	void turn();	// Turn on/off chunk
	void setVolume( sf::Uint8 volume );
	
	int getWidth();
	int getHeight();
	int getX();
	int getY();
	sf::Uint8 getAlpha();
};