#pragma once
#include "menu/circlebutton.h"
#include "menu/volume_button.h"
#include "play/game/loading_world/loading_world.h"
#include "level/chat.h"
#include "menu/pausesystem.h"
#include "own/music.h"

class Table
{
	// Basics.
	bool menu;
	bool level;
	bool run;
	
	// Objects.
	MySprite background;
	Circlebutton homebutton;
	Circlebutton levelbutton;
	Circlebutton chunkbutton;
	Circlebutton musicbutton;
	Volume_button chunk_volume;
	Volume_button music_volume;
	Chat chat;
	Pausesystem pausesystem;
	Music music;
	
public:
	
	// Basics.
	Table();
	~Table();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void head( sf::RenderWindow* &window, double elapsedTime );
	
	// Support.
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	void fades( double elapsedTime );
	
	// Sound.
	void setUsername( string line );
	void loadSound();
	void saveSound();
	
	// Getters.
	bool isMenu();
	bool isLevel();
};