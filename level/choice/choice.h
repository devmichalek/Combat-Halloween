/**
    choice.h
    Purpose: class Choice - choose world or random.

    @author Adrian Michalek
    @version 2016.12.13
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "menu/click.h"
#include <vector>

class Choice :public Click
{
	MySprite tick, cross;
	vector <bool> unlocked;
	vector <MySprite*> world;
	
	MySprite frame;		// frame around focused sprite
	MySprite button;	// "random" button
	
	MyText text;	// under sprites
	MyText information;	// left bottom corner
	vector <MyText*> description;
	
	int counter; 	// for random
	int result;		// latest result
	int chosen;		// if user choose one of images
	
	// To move - animation
	int range;
	bool keep;
	
	// Other stuff
	int alpha_line;
	int counter_line;
	
public:
	
	Choice();
	~Choice();
	void free();
	void reset( unsigned screen_w, unsigned screen_h );
	
	void load();
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	
	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
	
	// Getters.
	int getResult();
	float getBot();
	float getLeft();
	sf::Uint8 getAlpha();
	bool isChosen();
	float getWidth();
	
	bool move( int vel, int scope );	// move horizontal
};