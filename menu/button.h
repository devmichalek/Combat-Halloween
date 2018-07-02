#pragma once
#include "own/sprite.h"
#include "own/chunk.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Button
{
	MySprite button;
	bool locked;
	bool pressed;
	
	// Sound.
	Chunk click;
	
public:
	
	// Basics.
	Button();
	~Button();
	void free();
	
	void load( float x, float y, string path, bool locked = false );
	void setScale( float x, float y );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Getters.
	bool isPressed();
	void setPressed();
	float getBot();
	float getLeft();
	float getTop();
	
	// Setters.
	void lock();
	void unlock();
	void reload();
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
};