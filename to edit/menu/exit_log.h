#pragma once

#include "play_button.h"

class Exit_log :public Play_button
{

public:
	using::Play_button::Play_button;
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	int getState();
};