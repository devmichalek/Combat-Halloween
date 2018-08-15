#pragma once
#include "text.h"
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
	std::vector <cmm::Text*> texts;
	
public:
	Initialization();
	~Initialization();
	void free();

	void load(const float &screen_w, const float &screen_h);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

	const bool& isNext() const;
};