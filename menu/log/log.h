/**
    log.h
    Purpose: class Log - for simple buttons, after click you have clear window to show own stuff.

    @author Adrian Michalek
    @version 2016.10.07
	@email adrmic98@gmail.com
*/

#pragma once

#include "menu/click.h"
#include "drawable/text.h"
#include "drawable/sprite.h"
#include "menu/explanator/explanator.h"

class Log :public Click
{
	Explanator explanator;
	bool state;
	bool locked;
	MySprite button;
	
public:
	
	Log( bool locked = false );
    ~Log();
	void free();

    void load( string path, int left, int y );
	void setExplanator( string line, int screen_w );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	int getRight();
	const bool& getState();
};