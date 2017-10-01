#pragma once
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class Initialization
{
	enum	// Enum with states of texts.
	{
		AUTHOR = 0,
		PRESENTS,
		HALLOWEEN,
		COMBAT,
		AMOUNT
	};
	
	bool ready;
	sf::Uint8 state;
	vector <MyText*> texts;
	
public:
	
	// Basics.
	Initialization();
	~Initialization();
	void free();
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	// Next state.
	bool isReady();
};