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
#include "sound/music.h"
#include "show_scores.h"

class Panel_menu
{
	int state;
	
	Sound sound;
	Music* music;
	MySprite* bg;
	Replay_button* replay_button;
	Backtomenu_panel* backtomenu_panel;
	Show_scores* show_scores;
	
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
	
	void set( int scores, int type, bool status, int coruption );
	void setSound();
	void reloadMusic();
};