#pragma once
#include "tiles.h"

class Game
{
	// Basics.
	bool table;
	bool loaded;
	
	// Objects.
	MySprite background;
	
public:
	
	// Basics.
	Game();
	~Game();
	void free();
	
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
	
	// Getters.
	bool isTable();
	float getAlpha();
	
	// Loading.
	void loading( int which );
	bool isError();
	bool isSuccess();
};