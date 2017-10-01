#pragma once
#include "play/game/game.h"
#include "menu/circlebutton.h"
#include "menu/volume_button.h"
#include "play/game/loading_world/loading_world.h"
#include "level/chat.h"
#include "menu/pausesystem.h"
#include "own/music.h"

class Play
{
	// Basics.
	bool menu;
	bool level;
	int editor;
	bool run;
	
	// Objects.
	Game game;
	Circlebutton editorbutton;
	Circlebutton homebutton;
	Circlebutton levelbutton;
	Circlebutton chunkbutton;
	Circlebutton musicbutton;
	Volume_button chunk_volume;
	Volume_button music_volume;
	Loading_world loading_world;
	Chat chat;
	Pausesystem pausesystem;
	Music music;
	
public:
	
	// Basics.
	Play();
	~Play();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void head( sf::RenderWindow* &window, double elapsedTime );
	
	// Support.
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	void fades( double elapsedTime );
	
	// Sound and settings.
	void setMessage( string message );
	void setUsername( string line );
	void loadSound();
	void saveSound();
	
	// Getters.
	bool isMenu();
	bool isLevel();
	bool isTable();
	bool isEditor();
};