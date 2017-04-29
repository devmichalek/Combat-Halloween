/**
    link_button.h
    Purpose: class Link_button - for buttons, after click open website with special url.

    @author Adrian Michalek
    @version 2016.10.16
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "menu/click.h"
#include "menu/explanator/explanator.h"

class Link_button :public Click
{
    string url;
	Explanator explanator;
	
protected:
	
	bool locked;	// if true then we cannot click on the button
    MySprite button;

public:
	
	// Basics.
	Link_button( string url, bool locked = false );
	~Link_button();
	void free();
	
	void load( string path, float x, float y = 0 );
	void handle( sf::Event &event, bool side = false );
	void draw( sf::RenderWindow &window );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	// Extra.
	void setExplanator( string line );
	
	// Getters.
	float getBot();
	float getWidth();
	float getHeight();
};