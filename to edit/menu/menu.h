#pragma once

#include "menu/link_button.h"
#include "menu/play_button.h"
#include "menu/title.h"
#include "menu/music_button.h"
#include "menu/log.h"
#include "menu/exit_log.h"
#include "menu/music_volume.h"
#include "menu/keyboard.h"
#include "templates/music.h"
#include "menu/setkeyboard.h"
#include "menu/information.h"

class Menu
{
	int state;
	bool playmusic;
	bool playchunk;
	sf::Uint8 musicvolume_value;
	sf::Uint8 chunkvolume_value;
	
	// Menu objects
	Link_button* git_button;
	Link_button* google_button;
	Link_button* twitter_button;
	Link_button* facebook_button;
	MySprite* background;
	Play_button* play_button;
	Title* title;
	Music_button* music_button;
	Music_button* chunk_button;
	Log* author_log;
	Log* game_log;
	Log* settings_log;
	Log* scores_log;
	Exit_log* exit;
	Music* music;
	Music_volume* music_volume;
	Music_volume* chunk_volume;
	Keyboard* keyboard;
	MyText* version;
	Setkeyboard* setkeyboard;
	Information* information;
	
public:
	
	Menu();
    ~Menu();
    void free();
	
    void load( int screen_width, int screen_height );

    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool isQuit();
	bool nextState();
	
	bool musicOn();
	bool chunkOn();
	sf::Uint8 getChunkVolume();
	sf::Uint8 getMusicVolume();
};