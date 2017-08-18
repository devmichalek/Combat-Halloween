#pragma once
#include "own/text.h"
#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Loading_world
{
	// Support.
	float screen_w;
	float screen_h;
	bool ready;
	bool stop;
	
	// Current progress.
	sf::Uint8 state;		// Show percents.
	MyText info;
	
	// Animation
	float counter;		// To set offsets.
	float max;			// How many offset's.
	MySprite progress_bar;
	
public:
	
	// Basics.
	Loading_world();
	~Loading_world();
	void free();
	
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window, double elapsedTime );
	
	// In addition.
	const sf::Uint8& getState();
	bool isReady();
	void unStop();
	bool getStop();
	
	// Support.
	void setError();
	void setSuccess();
};