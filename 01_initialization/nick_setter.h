#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"

class Nick_setter
{
	MySprite label;
	MyText text;
	float y_state;
	
	unsigned min, max;
	int amount;
	
	bool release;
	string nick;
	bool next;
	
public:
	
	Nick_setter();
	~Nick_setter();
	void free();
	
	void load( int screen_w, int screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	void reloadPosition();
	bool isPossibleKey( sf::Event &event );
	string getName( int n );
	bool nextState();
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
};