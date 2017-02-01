/**
    menu.h
    Purpose: class Menu is a huge container with buttons in menu state.

    @author Adrian Michalek
    @version 2016.11.20
	@email adrmic98@gmail.com
*/

#pragma once

#include "sound/sound.h"
#include "title.h"
#include "sound_button.h"
#include "volume_button.h"
#include "link_button.h"
#include "play_button.h"
#include "log.h"
#include "exit_log.h"
#include "sound/music.h"
#include "information.h"
#include "keyboard.h"


class Menu
{
	int state;
	
	// Menu objects
	Sound sound;
	
	Title* title;
	
	Sound_button* music_button;
	Sound_button* chunk_button;
	
	Volume_button* music_volume;
	Volume_button* chunk_volume;
	
	Link_button* git_button;
	Link_button* google_button;
	Link_button* twitter_button;
	Link_button* facebook_button;
	
	MySprite* background;
	
	Play_button* play_button;
	
	Log* author_log;
	Log* game_log;
	Log* settings_log;
	Log* scores_log;
	
	Exit_log* exit;
	
	Music* music;
	
	MyText* version;
	
	Information* information;
	Keyboard* keyboard;
	
public:
	
	Menu();
    ~Menu();
    void free();
	
    void load( int screen_w, int screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool isQuit();
	bool nextState();
	
	int getState();
	Sound getSound();
	void set( int state, Sound* sound );
	
	void reloadMusic();
};