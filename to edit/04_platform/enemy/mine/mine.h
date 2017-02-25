#pragma once

#include "04_platform/world/brick/block.h"
#include <SFML/Graphics/Color.hpp>

class Mine
{
	sf::Uint8 nr;
	int x1, x2, y;
	int state;
	int offset;
	sf::Uint8 delay;
	sf::Uint8 counter;
	
	sf::Uint8 line_one;
	sf::Uint8 line_two;
	
	bool harmed;
	bool exploded;
	bool ticktocked;
	
public:

	Mine();
	~Mine();
	void free();
	void reset();
	
	// Getters.
	int getX();
	int getY();
	
	// Set as active.
	void setActive();
	
	// In action.
	void moveX( int vel );
	
	
	
	
	bool harm();
	void mechanics();
	void positioning( int x1, int x2, int y );
	
	bool ableToDraw();
	bool ableToDestroy();
	bool explosion();
	bool ticktock();
	
	// getters
	sf::Uint8 getNr();
	sf::Uint8 getOffset();
};