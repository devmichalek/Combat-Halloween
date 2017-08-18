#pragma once
#include "worldtable.h"
#include "menu/circlebutton.h"
#include "menu/volume_button.h"
#include "level/chat.h"
#include "menu/pausesystem.h"
#include "own/music.h"

class Level
{
	// Basics.
	bool back;
	bool next;
	bool run;
	
	// Objects.
	MySprite background;
	Worldtable worldtable;
	Circlebutton homebutton;
	Circlebutton playbutton;
	Circlebutton updatebutton;
	Circlebutton chunkbutton;
	Circlebutton musicbutton;
	Volume_button chunk_volume;
	Volume_button music_volume;
	Chat chat;
	Pausesystem pausesystem;
	Music music;
	
public:
	
	// Basics.
	Level();
	~Level();
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
	bool isNext();
	bool isBack();
};