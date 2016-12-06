#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "menu/click.h"

class Music_volume :public Click
{
	float volume;
	sf::Uint8 last_volume;
	MySprite plus;
	MySprite minus;	// background
	MyText text;		
	MyText percent;
	
	
	// hover
	bool plus_focus;
	bool minus_focus;
	
public:
	
	Music_volume( float volume = 1 );
	~Music_volume();
	
	void load( int left, int y, string str );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	int getBot();
	
	bool changeVolume();
	sf::Uint8 getVolume();
	
	int getRight();
};