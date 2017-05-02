/**
    bonus_choice.h
    Purpose: class Bonus_choice - choose additional world.

    @author Adrian Michalek
    @version 2017.04.29
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "menu/click.h"
#include <vector>

class Bonus_choice :public Click
{
	vector <bool> unlocked;
	vector <MySprite*> world;
	
	int result;		// latest result
	
	// To move - animation
	int range;
	bool keep;
	
public:
	
	Bonus_choice();
	~Bonus_choice();
	void free();
	void reset( float x, float y, float w );
	
	void load();
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	
	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
	
	// Getters.
	int getResult();
	bool isChosen();
	
	bool move( int vel, int scope );	// move horizontal
};