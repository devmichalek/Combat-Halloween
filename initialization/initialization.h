#pragma once
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class Initialization
{
	// Enum with states of texts.
	enum
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
	
	Initialization();
	~Initialization();
	void free();
	
	void load( int screen_width, int screen_height );
	void draw( sf::RenderWindow* &window, double elapsedTime );
	
	// Next state.
	bool isReady();
};