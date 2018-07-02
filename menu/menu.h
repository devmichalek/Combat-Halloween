<<<<<<< HEAD
/**
    menu.h
    Purpose: class Menu is a huge container with buttons in menu state.

    @author Adrian Michalek
    @version 2016.11.20
	@email adrmic98@gmail.com
*/

#pragma once

#include "sound/sound.h"
#include "title/title.h"
#include "sound_button/sound_button.h"
#include "volume_button/volume_button.h"
#include "link_button/link_button.h"
#include "play_button/play_button.h"
#include "log/log.h"
#include "play_button/exit_log.h"
#include "sound/music.h"
#include "keyboard/information.h"
#include "keyboard/keyboard.h"
#include "development/developdeck.h"
#include "reset_button/reset_button.h"
#include "development/headdeck.h"
#include "nick/nick.h"
#include "author_log/author.h"

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
	Link_button* scores_button;
	
	Play_button* play_button;
	
	Log* author_log;
	Log* game_log;
	Log* settings_log;
	Log* skill_log;
	
	Exit_log* exit;
	
	Music* music;
	
	Information* information;
	Keyboard* keyboard;
	
	Development* development;
	Headdeck* headdeck;
	
	Reset_button* reset_button;
	
	Nick* nick;
	Author* author;
=======
#pragma once
#include "knight_specs.h"
#include "link_button.h"
#include "button.h"
#include "circlebutton.h"
#include "settings.h"
#include "volume_button.h"
#include "information.h"
#include "level/chat.h"
#include "pausesystem.h"
#include "own/music.h"

class Menu
{
	// Basics.
	bool ready;
	bool close;
	bool editor;
	bool run;
	
	// Objects.
	MySprite background;
	Knight_specs knight_specs;
	Link_button github;
	Link_button scores;
	Link_button website;
	Button singleplayer;
	Button multiplayer;
	Button exit;
	Circlebutton chunkbutton;
	Circlebutton musicbutton;
	Circlebutton updatebutton;
	Circlebutton reloadbutton;
	Circlebutton settingsbutton;
	Settings settings;
	Volume_button chunk_volume;
	Volume_button music_volume;
	Information information;
	Chat chat;
	Pausesystem pausesystem;
	Music music;
>>>>>>> Combat-Halloween/master
	
public:
	
	// Basics.
	Menu();
<<<<<<< HEAD
    ~Menu();
    void free();
	
    void load( unsigned screen_w, unsigned screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	// Extra.
	bool isQuit();
	bool nextState();
	void reloadMusic();
	void checkMoney();
	void setNick();
=======
	~Menu();
	void free();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void head( sf::RenderWindow* &window, double elapsedTime );
	
	// Support.
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	void fades( double elapsedTime );
	
	// Sound and username.
	void setUsername( string line );
	void loadSound();
	void saveSound();
	
	// Getters.
	bool isReady();
	bool isClose();
	bool isEditor();
>>>>>>> Combat-Halloween/master
};