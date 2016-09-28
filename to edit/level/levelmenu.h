#pragma once

#include "level/select.h"
#include "templates/music.h"
#include "level/backtomenu.h"

class Level_menu
{
	int state;
	int which_level;
	bool playmusic;
	bool playchunk;
	sf::Uint8 musicvolume;
	sf::Uint8 chunkvolume;
	
	Select* select;
	MySprite* background;
	Music* music;
	Backtomenu* backtomenu;
	
public:

	Level_menu();
    ~Level_menu();
    void free();
	
	void setStartPackage( bool a, bool b, sf::Uint8 cv, sf::Uint8 mv ); // chunk, music isOn?, volumes
    void load( int screen_w, int screen_h );

    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool isQuit();
	bool nextState();
	bool backToMenu();
	
	bool musicOn();
	bool chunkOn();
	sf::Uint8 getChunkVolume();
	sf::Uint8 getMusicVolume();
	int getLevel();
};