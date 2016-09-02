#pragma once

#include "sprite.h"

class Menu_play_button
{
	int state;
	MySprite mySprite;
	
public:
	
	Menu_play_button();
    ~Menu_play_button();

    bool load( int screen_w, int bot );
    void draw( RenderWindow* &window );
    void handle( Event &event );
	
	int getBot();
	int getState();
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
};