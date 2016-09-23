#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "templates/chunk.h"

class Music_volume // music || chunk, volume
{
	int volume;
	int last_volume;
	MySprite green_bar;
	MySprite white_bar;	// background
	MyText text;		
	MyText percent;
	
	// click as sound and play as state
	bool play;
	Chunk click;
	
public:
	
	Music_volume( int volume = 1 );
	~Music_volume();
	
	void load( int screen_w, int y, string str );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	int getBot();
	void turn();	// Turn on/off chunk
	void setVolume( sf::Uint8 volume );
	
	bool changeVolume();
	sf::Uint8 getVolume();
};