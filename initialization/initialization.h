/**
    initialazation.h
    Purpose: class Initialization - contains nick stuff.

    @author Adrian Michalek
    @version 2017.04.22
	@email adrmic98@gmail.com
*/

#pragma once

#include "nick_setter.h"
#include "nick_info.h"

class Initialization
{
	bool next;
	
	Nick_setter nick_setter;
	Nick_info nick_info;
	
public:
	
	// Basics.
	Initialization();
    ~Initialization();
    void free();
	
    void load( unsigned screen_w, unsigned screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	// Extra.
	bool nextState();
};