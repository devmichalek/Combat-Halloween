#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "templates/chunk.h"

class Menu_play_button
{

protected:
	int state;
	MySprite mySprite;
	MyText myText;
	
	// click as sound and play as state
	bool play;
	Chunk click;
	
public:
	
	Menu_play_button();
    ~Menu_play_button();

    void load( int screen_w, int bot );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	int getBot();
	int getX();
	int getState();
	bool nextGameState();
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	void turn();	// Turn on/off chunk
};