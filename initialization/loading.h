#pragma once
#include "own/text.h"
#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Loading
{
	// Support.
	float screen_w;
	float screen_h;
	bool ready;
	
	// Current progress.
	MyText text;			// Text "loading".
	sf::Uint8 state;		// Show percents.
	
	// Animation
	float counter;		// To set offsets.
	float max;			// How many offset's.
	MySprite progress_bar;
	
public:
	
	// Basics.
	Loading();
	~Loading();
	void free();
	
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window, double elapsedTime );
	
	// In addition, getters.
	const sf::Uint8& getState() const;
	bool isReady();
	void beReady();
	
	// Support.
	void setText();
};