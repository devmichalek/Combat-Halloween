#pragma once
#include <SFML/Graphics/Rect.hpp>

class EAEntitySpecial	// like knight, one and only
{
	sf::FloatRect rect;
public:
	EAEntitySpecial();
	~EAEntitySpecial();
private:
	void free();
public:
	void reset();

	void init(const float& w, const float& h);
	void add(const float& x, const float& y);
	bool remove(const float& x, const float& y);
	sf::Vector2f get();	// pos x y
	bool isSet();
};