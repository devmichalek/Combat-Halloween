/**
    exit_log.h
    Purpose: class Exit_log to show exit state.

    @author Adrian Michalek
    @version 2016.10.27
	@email adrmic98@gmail.com
*/

#pragma once

#include "play_button.h"

class Exit_log :public Play_button
{
	MyText myText;

public:
	
	// Basics.
	Exit_log();
	~Exit_log();
	void free();
	
	void load( unsigned w, unsigned h );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	// Getter.
	int getState();
	
	// Window.
	void setScale( float s_x, float s_y );
	void setView( unsigned w, unsigned h, int r_x, int r_y );
};