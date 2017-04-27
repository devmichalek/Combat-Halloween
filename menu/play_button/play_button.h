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
	
	float scale;
	
public:
	
	// Basics.
	Play_button();
    ~Play_button();
	void free();

    void load( unsigned w, unsigned h );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event, int r_x, int r_y );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	// Mutator.
	void setState( int state );	
	
	// Getters.
	const int getBot() const;
	const int getX() const;
	const sf::Uint8& getState() const;
	
	// Extra.
	bool nextState() const;
	
	// Window.
	void setScale( float s_x, float s_y );
	void setView( unsigned w, unsigned h, int r_x, int r_y );
};