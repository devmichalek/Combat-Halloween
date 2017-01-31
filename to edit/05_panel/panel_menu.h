#pragma once

#include "sound/sound.h"
#include "replay_button.h"
#include "backtomenu_panel.h"

class Panel_menu
{
	int state;
	Sound* sound;
	
	MySprite* bg;
	Replay_button* replay_button;
	Backtomenu_panel* backtomenu_panel;
	
public:
	
	Panel_menu();
    ~Panel_menu();
    void free();
	
    void load( int screen_w, int screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	void set( int state, Sound* sound );
	void reset();
	int getState();
	
	bool backToMenu();
	bool backToPlatform();
};