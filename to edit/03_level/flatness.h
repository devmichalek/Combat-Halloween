#pragma once

#include "drawable/text.h"
#include "drawable/sprite.h"
#include "02_menu/click.h"

class Flatness :public Click
{
	string text_one;
	string text_two;
	
	MyText text;
	MyText percent_text;
	MySprite white_bar;
	MySprite green_bar;
	
	// To move - animation
	int range;
	int blocks;
	bool keep;
	
	int percent;
	int percent_state;
	
public:
	Flatness( string text_one, string text_two, int percent );
	~Flatness();
	void free();
	void reset( int addX, unsigned screen_w, unsigned screen_h, int bot );


	void load( int addX, unsigned screen_w, unsigned screen_h, int bot );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	
	
	void fadein( int j = 1, int max = 0xFF );
	void fadeout( int j = 1, int min = 0 );
	
	int getResult();
	bool move( int vel, int scope );	// move horizontal
	
	int getBot();
};