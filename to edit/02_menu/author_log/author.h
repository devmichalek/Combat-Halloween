#pragma once

#include "scroll.h"
#include "list.h"
#include "author_info.h"

class Author
{
	bool reset_done;
	
	Scroll scroll;
	List list;
	Author_info author_info;
	
public:
	
	Author();
    ~Author();
	void free();
	void reset();

    void load( int screen_w, int screen_h );
    void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
};