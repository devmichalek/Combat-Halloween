#pragma once

#include "templates/sprite.h"
#include "menu/click.h"

class Link_button :public Click
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
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
};