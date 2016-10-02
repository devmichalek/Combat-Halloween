#pragma once

#include "menu/link_button.h"

class Backtomenu :public Link_button
{
	int state;
	
public:

	using Link_button::Link_button;
	
	void load( int screen_w );
	void handle( sf::Event &event );
	
	void setState( int here );
	int getState();
};