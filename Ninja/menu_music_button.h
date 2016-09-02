#pragma once

#include "sprite.h"


class Menu_music_button
{
	MySprite music_button;
	MySprite scratch;
	bool focus;
	
	int scratch_state;
	
public:

	Menu_music_button( int scratch_state = 0 );
    ~Menu_music_button();

	bool load( string path, int bot );
    void draw( RenderWindow* &window );
    void handle( Event &event );

	int getBot();
	int getState();
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
};