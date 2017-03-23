/**
    panel_menu.h
    Purpose: class Panel_menu as a main class in panel state.

    @author Adrian Michalek
    @version 2017.02.22
	@email adrmic98@gmail.com
*/

#pragma once

#include "sound/sound.h"
#include "replay_button.h"
#include "backtomenu_panel.h"

class Panel_menu
{
	int state;
	
	Sound sound;
	MySprite* bg;
	Replay_button* replay_button;
	Backtomenu_panel* backtomenu_panel;
	
public:
	
	Panel_menu();
    ~Panel_menu();
    void free();
	void reset();
	
    void load( int screen_w, int screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	int getState();
	void setState( int state );
	
	bool backToMenu();
	bool backToPlatform();
	
	void setSound();
	void reloadMusic();
};