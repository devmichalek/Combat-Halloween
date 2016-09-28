#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "menu/parentchunk.h"

class Music_volume :public Parentchunk
{
	float volume;
	int last_volume;
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
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	int getBot();
	
	bool changeVolume();
	sf::Uint8 getVolume();
	
	int getRight();
};