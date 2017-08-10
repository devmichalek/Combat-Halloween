#pragma once

#include "own/chunk.h"
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Pausesystem
{
	MySprite blackout;
	MyText text;
	
	bool active;
	bool release;
	
	// Sound.
	Chunk click;
	
public:
	
	// Basics.
	Pausesystem();
	~Pausesystem();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// The rest.
	bool isActive();
	void setActive( bool active );
	int getAlpha();
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
};