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
	
	// Basics.
	Author();
    ~Author();
	void free();
	void reset();

    void load( unsigned screen_w, unsigned screen_h );
    void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
};