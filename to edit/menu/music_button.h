#pragma once

#include "templates/sprite.h"
#include "menu/parentchunk.h"


class Music_button :public Parentchunk	// Class for chunk/music button 
{
	MySprite button;
	MySprite scratch;
	
	// music/chunk is on/off
	int state;
	
public:

	Music_button( bool play = true );
    ~Music_button();

	void load( string path, int bot );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );

	int getBot();
	bool change();

	void fadein( int i, int max = 255 );
	void fadeout( int i, int min = 0 );
};