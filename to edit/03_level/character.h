/**
    character.h
    Purpose: class Character - shows 2 animations in level state and allow to choose what of them, then game starts.

    @author Adrian Michalek
    @version 2016.12.06
	@email adrmic98@gmail.com
*/

#pragma once

#include "02_menu/click.h"
#include "drawable/text.h"
#include "drawable/sprite.h"

class Character :public Click
{
	MySprite one;
	MySprite two;
	
	MyText text;
	MyText information;
	
	int ready;
	int result;
	
	// Idle animation
	int offset;
	int how_many;
	
	// To move - animation
	int range;
	bool keep;
	
	// Other stuff
	sf::Uint8 delay;
	sf::Uint8 alpha_line;
	
public:
	
	Character();
    ~Character();
	void free();
	void reset( int screen_w, int screen_h );


    void load( int screen_w, int screen_h );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	
	void fadein( int j = 1, int max = 0xFF );
	void fadeout( int j = 1, int min = 0 );
	
	int getAlpha();
	bool move( int vel, int scope );	// move horizontal
	
	bool nextState();
	int getResult();
};