#pragma once

#include "templates/sprite.h"
#include "templates/chunk.h"


class Music_button	// Class for chunk/music button 
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

	Music_button( bool play = true );
    ~Music_button();

	void load( string path, int bot );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );

	int getBot();
	bool change();
	void turn();
	
	void fadein( int i, int max = 255 );
	void fadeout( int i, int min = 0 );
};