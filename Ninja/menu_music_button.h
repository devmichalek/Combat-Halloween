#pragma once

#include "sprite.h"
#include "chunk.h"


class Menu_music_button	// Class for chunk/music button 
{
	MySprite button;
	MySprite scratch;
	
	// focus on button true/false
	bool focus;
	
	// music/chunk is on/off
	int state;
	
	// click as sound and play as state
	bool play;
	Chunk click;
	
public:

	Menu_music_button( bool play = true );
    ~Menu_music_button();

	bool load( string path, int bot );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );

	int getBot();
	bool change();
	void turn();
	
	void fadein( int i, int max = 255 );
	void fadeout( int i, int min = 0 );
};