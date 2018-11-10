#pragma once
#include "state.h"
#include "text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class Initialization final : public cmm::State
{
	enum	// Enum with states of texts.
	{
		AUTHOR = 0,
		PRESENTS,
		HALLOWEEN,
		COMBAT,
		AMOUNT
	};
	
	sf::Uint8 state;
	std::vector <cmm::Text*> texts;
	
public:
	Initialization();
	~Initialization();
	void free();
	
	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event) {}
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

private: bool isReady() const; public:
	void setState(int &state);
};