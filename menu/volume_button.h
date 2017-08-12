#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include "own/chunk.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Volume_button
{
	MySprite plus;
	MySprite minus;
	
	float volume;
	float min, max;
	
	bool active;
	bool plus_pressed;
	bool minus_pressed;
	
	// Sound.
	Chunk click;
	
public:
	
	// Basics.
	Volume_button();
	~Volume_button();
	void free();
	
	void load( float left, float right, float bot, float screen_w, float screen_h );
	bool handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Getters and setters.
	void setMainVolume( float volume );
	float getMainVolume();
	void setActive( bool active );
	bool isChanged();	// whenever is minus button pressed or plus button pressed.
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
};