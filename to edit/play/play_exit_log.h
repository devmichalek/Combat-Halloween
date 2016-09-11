#pragma once

#include "menu/menu_play_button.h"

class Play_exit_log :public Menu_play_button
{

public:
	using::Menu_play_button::Menu_play_button;
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	int getState();
};