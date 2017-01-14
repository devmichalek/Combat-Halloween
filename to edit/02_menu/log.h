#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "menu/click.h"

class Log :public Click
{
	int state;
	MySprite button;
	MySprite log;
	
	sf::Uint8 nr;	// how many text textures
	MyText* myText;
	
	// if that log is not ready
	bool locked;
	
	// if we don't want to render window texture
	bool win;
	
public:
	
	Log( bool locked = false, bool win = true );
    ~Log();

    void load( string path, int left, int y, int screen_w );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	int getRight();
	const int& getState() const;
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
};