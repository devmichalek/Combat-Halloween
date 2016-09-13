#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "templates/chunk.h"

class Menu_log
{
	int state;
	MySprite button;
	MySprite log;
	
	int nr;	// how many text textures
	MyText* myText;
	
	// click as sound and play as state
	bool play;
	Chunk click;
	
	// if that log is not ready
	bool locked;
	
	// if we don't want to render window texture
	bool win;
	
public:
	
	Menu_log( bool locked = false, bool win = true );
    ~Menu_log();

    void load( string path, int left, int y, int screen_w );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	int getRight();
	int getState();
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	void turn();	// Turn on/off chunk
};