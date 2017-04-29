/**
    nick_setter.h
    Purpose: class Nick_setter - set your own nick -mechanics.

    @author Adrian Michalek
    @version 2017.04.22
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"

class Nick_setter
{
	MyText text;
	MySprite label;
	
	unsigned min, max;
	int amount;
	
	bool release;
	string nick;
	
	bool next;
	
public:
	
	// Basics.
	Nick_setter();
	~Nick_setter();
	void free();
	
	void load( unsigned screen_w, unsigned screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	// In Addition.
	void reloadPosition(); 					// Reload text position.
	bool isPossibleKey( sf::Event &event ); // Checks if that key is possible.
	string getName( int n );				// Get string name of this key.
	bool nextState();						// Are we ready?
};