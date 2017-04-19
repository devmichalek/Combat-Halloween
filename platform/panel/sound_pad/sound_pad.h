#pragma once

#include "drawable/sprite.h"
#include "menu/click.h"

class Sound_pad :public Click
{
	bool music_state;
	bool chunk_state;
	
	bool mus_scratch;
	bool chu_scratch;
	
	MySprite scratch;
	MySprite music;
	MySprite chunk;
	
public:
	
	Sound_pad();
	~Sound_pad();
	void free();
	
	void setChunk( bool s );
	void setMusic( bool s );
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	bool musicChanged();
	bool chunkChanged();
};