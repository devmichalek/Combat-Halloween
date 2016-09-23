#pragma once

#include "level/select.h"

class Level_menu
{
	int state;
	bool playmusic;
	bool playchunk;
	sf::Uint8 musicvolume;
	sf::Uint8 chunkvolume;
	
	Select* select;
	MySprite* background;
	
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
	
	bool musicOn();
	bool chunkOn();
	sf::Uint8 getChunkVolume();
	sf::Uint8 getMusicVolume();
};