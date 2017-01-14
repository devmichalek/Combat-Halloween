#pragma once

#include "templates/sprite.h"
#include "menu/click.h"

// Class for chunk/music button
class Music_button :public Click
{
	MySprite button;
	MySprite scratch;
	
	// music/chunk is on/off
	sf::Uint8 state;
	
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