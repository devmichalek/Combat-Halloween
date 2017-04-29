#pragma once

#include "drawable/text.h"

class Member
{
	bool url_state;
	string url;
	bool focus;
	sf::Uint8 offset;
	
	float button_x_c, x_c;	// changeable
	float button_x, button_y;
	
	MyText text;
	
public:
	
	// Basic information.
	Member();
	~Member();
	void free();
	void reset();
	
	void load( string text, bool s = false, string url = "" );
	void setPosition( float x, float y );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	// Extra.
	void move( float distance );
	
	bool isButton();
	float getButtonX();
	float getButtonY();
	string getURL();
	float getY();
	
	sf::Uint8& getOffset();
	bool& getFocus();
};