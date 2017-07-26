#pragma once

#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class Initialization
{
	enum
	{
		adrmic = 0,
		pres,
		part,
		title
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
	
	bool isReady();
};