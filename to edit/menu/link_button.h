#pragma once

#include "templates/sprite.h"
#include "menu/parentchunk.h"

class Link_button :public Parentchunk
{
    string url;
	
protected:
	
	bool locked;
    MySprite button;

public:
	
    Link_button( string url, bool locked = false );
    ~Link_button();

    void load( string path, int screen_w, int bot = 10 );
    void draw( sf::RenderWindow &window );
	void handle( sf::Event &event );
	
	int getBot();	// getter
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
};