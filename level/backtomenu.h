/**
    backtomenu.h
    Purpose: class Backtomenu - button with function "back to menu".

    @author Adrian Michalek
    @version 2016.12.05
	@email adrmic98@gmail.com
*/

#pragma once

#include "menu/link_button/link_button.h"

class Backtomenu :public Link_button
{
	int state;
	
public:

	using Link_button::Link_button;
	
	void load( int screen_w );
	void handle( sf::Event &event );
	
	void setState( int state );
	int getState();
};