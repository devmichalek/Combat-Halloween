/**
    nick_info.h
    Purpose: class Nick_info - responsible for drawing information about nick.

    @author Adrian Michalek
    @version 2017.04.22
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/text.h"

class Nick_info
{
	vector <MyText*> texts;
	
public:
	
	// Basics.
	Nick_info();
	~Nick_info();
	void free();
	
	void load( int w, int h );
    void draw( sf::RenderWindow* &window );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	// Additional.
	sf::Uint8 getAlpha();
	
	// Window.
	void setScale( float s_x, float s_y );
	void setView( int w, int h, int r_x, int r_y );
};