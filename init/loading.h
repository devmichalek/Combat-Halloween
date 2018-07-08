#pragma once
#include "text.h"
#include "sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Loading
{
	// Support.
	float screen_w;
	float screen_h;
	bool ready;
	
	// Current progress.
	cmm::Text text;			// Text "loading".
	sf::Uint8 state;		// Show percents.
	cmm::Sprite progress_bar;
	
public:
	Loading();
	~Loading();
	void free();
	void load(float screen_w, float screen_h);
	void draw(sf::RenderWindow* &window);
	void mechanics(double elapsedTime);
	
	const sf::Uint8& getState() const;
	bool isReady() const;
	
	void beReady();
private:
	void setText();
};