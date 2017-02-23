#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "02_menu/click.h"
#include <vector>

class Difficulty :public Click
{
	MyText corruption;
	
	vector <MyText*> texts;
	vector <MySprite*> sprites;
	
	int result;
	int alpha_line;
	
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
	
	void fadein( int j = 1, int max = 0xFF );
	void fadeout( int j = 1, int min = 0 );

	int getDifficulty();
	bool move( int vel, int scope );	// move horizontal
};