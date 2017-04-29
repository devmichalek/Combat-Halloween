/**
    backtomenu_panel.h
    Purpose: class Backtomenu_panel as a simple button with label 'menu'.

    @author Adrian Michalek
    @version 2017.02.27
	@email adrmic98@gmail.com
*/

#pragma once

#include "menu/play_button/play_button.h"

class Backtomenu_panel :public Play_button
{
	
protected:
	
	MyText myText;
	
public:
	
	void load( float x, float y );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
};