#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include "own/chunk.h"
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Chat
{
	float screen_w;
	float screen_h;
	
	// Background.
	MySprite background;
	
	// Sound.
	Chunk click;
	
public:
	
	// Basics.
	Chat();
	~Chat();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
};