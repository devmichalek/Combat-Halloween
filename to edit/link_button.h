#pragma once

#include "sprite.h"
#include "chunk.h"

class Link_button
{
    bool locked;
    string url;
    MySprite button;
	
	// focus on button true/false
	bool focus;	
	
	// click as sound and play as state
	bool play;
	Chunk click;

public:

    Link_button( string url, bool locked = false );
    ~Link_button();

    bool load( string path, int screen_w, int bot = 10 );
    void draw( sf::RenderWindow &window );
	void handle( sf::Event &event );
	
	int getBot();
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	void turn();	// Turn on/off chunk
};