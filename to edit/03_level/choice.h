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
#include "02_menu/click.h"

class Choice :public Click
{
	MySprite button;
	MyText text;
	
	sf::Uint8 nr;		// number of worlds
	MySprite* world;
	
	MySprite frame;
	MyText information;
	
	int counter; 	// for random
	int result;		// latest result
	int chosen;		// if user choose one of images
	
	// To move - animation
	int range;
	bool keep;
	
public:
	
	Choice();
	~Choice();

	void load( int screen_w, int screen_h );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	
	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
	
	int getResult();
	sf::Uint8 getAlpha();
	bool isChosen();
	
	void reset( int screen_w, int screen_h );
	
	bool move( int vel, int scope );	// move horizontal
};