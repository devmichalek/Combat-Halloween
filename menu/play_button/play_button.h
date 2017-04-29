/**
    play_button.h
    Purpose: class Play_button - for button 'play' to start game, contain state.

    @author Adrian Michalek
    @version 2016.10.03
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "menu/click.h"

class Play_button :public Click
{

protected:

	mutable sf::Uint8 state;
	mutable MySprite mySprite;
	
public:
	
	// Basics.
	Play_button();
    ~Play_button();
	void free();

    void load( unsigned screen_w, unsigned screen_h );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	// Mutator.
	void setState( int state );	
	
	// Getters.
	const float getBot() const;
	const float getX() const;
	const sf::Uint8& getState() const;
	
	// Extra.
	bool nextState() const;
};