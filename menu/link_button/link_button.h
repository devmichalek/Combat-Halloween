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
	
	float x_state;
	float y_state;
	float y_buf;
	
	int screen_w;
	int screen_h;
	float scale;

public:
	
	// Basics.
	Link_button( string url, bool locked = false );
	~Link_button();
	void free();
	
	void load( string path, unsigned w, unsigned h, float l, float y = 10 );
	void handle( sf::Event &event, int r_x, int r_y, bool r = false );
	void draw( sf::RenderWindow &window );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	// Extra.
	void setExplanator( string line );
	
	// Getters.
	float getBot();
	float getWidth();
	float getHeight();
	
	// Window.
	void setScale( float s_x, float s_y );
	void setViewH( int w, int r_x, int r_y );
	void setViewW( int h, int r_x, int r_y );
};