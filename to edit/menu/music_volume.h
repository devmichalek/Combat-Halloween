#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "templates/chunk.h"

class Music_volume
{
	float volume;
	int last_volume;
	MySprite plus;
	MySprite minus;	// background
	MyText text;		
	MyText percent;
	
	// click as sound and play as state
	bool play;
	Chunk click;
	
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
	void turn();	// Turn on/off chunk
	void setVolume( sf::Uint8 volume );
	
	bool changeVolume();
	sf::Uint8 getVolume();
	
	int getRight();
};