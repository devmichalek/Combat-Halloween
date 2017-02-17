#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "02_menu/click.h"
#include <vector>

class Difficulty :public Click
{
	MySprite poi;
	MySprite graph;
	vector <MyText*> text;
	
	int offset;
	int delay;
	int state;
	
	int result;
	
	// Moving animation
	int range;
	bool keep;
	
public:

	Difficulty();
	~Difficulty();
	void free();
	void reset( int left, int bot );
	void load( int left, int bot );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
	
	void setDifficulty( int value );
	int getDifficulty();
	
	bool move( int vel, int scope );	// move horizontal
};