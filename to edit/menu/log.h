#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "menu/parentchunk.h"

class Log :public Parentchunk
{
	int state;
	MySprite button;
	MySprite log;
	
	int nr;	// how many text textures
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
	int getState();
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
};