#pragma once

#include "menu_play_button.h"

class Exit_log :public Exit_log
{

public:
	using::Exit_log::Exit_log;
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	int getState();
};