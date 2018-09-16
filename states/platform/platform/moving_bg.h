#pragma once
#include "sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

class MovingBG
{
	float screen_w;
	float screen_h;
	float velocity;

	std::vector<int> types;
	std::vector<sf::Vector2f> fs;
	std::vector<cmm::Sprite*> sprites;

public:
	MovingBG();
	~MovingBG();
	void free();
	void load(const float &screen_w, const float &screen_h);
	void draw(sf::RenderWindow* &window/*, sf::Shader &shader*/);
	void mechanics(const float &elapsedTime, const float &direction);
	const float& getAlpha() const;
};