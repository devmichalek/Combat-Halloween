#pragma once
#include <SFML/Graphics/Color.hpp>

#define MAX_ALPHA 255.0f
#define MIN_ALPHA 0.0f

namespace cmm
{
	// Log Colors
	const sf::Color ERROR_COLOR(0xF2, 0x58, 0x3E);
	const sf::Color WARNING_COLOR(0x78, 0x28, 0x8C);
	const sf::Color SUCCESS_COLOR((int)MAX_ALPHA, 0xDE, (int)MIN_ALPHA);

	// Basic Colors
	const sf::Color RED_COLOR(0xF2, 0x58, 0x3E);
	const sf::Color GREEN_COLOR(0x58, 0x70, 0x58);
	const sf::Color BLUE_COLOR(0x1E, 0x90, (int)MAX_ALPHA);
	const sf::Color CYAN_COLOR(0xB0, 0xC4, 0xDE);
	const sf::Color WHITISH_COLOR(0xE5, 0xE5, 0xE5);
	const sf::Color GRAYISH_COLOR(0x68, 0x68, 0x68);

	// Other Colors
	const sf::Color IRON_COLOR(0xBA, 0xBA, 0xBA);
	const sf::Color DULL_IRON_COLOR(0xD5, 0xE1, 0xDD);
	const sf::Color LOCKED_COLOR(0xDD, 0xDD, 0xDD);
	const sf::Color LOADING_COLOR((int)MAX_ALPHA, (int)MAX_ALPHA, (int)MAX_ALPHA);
	const sf::Color BACKGROUND_COLOR(21, 21, 29, (int)MAX_ALPHA);
}