#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics/Color.hpp>

namespace cmm
{
	class LogConsole
	{
	public:
		LogConsole();
		~LogConsole();
		void clear();

		static sf::Color getErrorColor()	{ return sf::Color(0xF2, 0x58, 0x3E); }
		static sf::Color getWarningColor()	{ return sf::Color(0x78, 0x28, 0x8C); }
		static sf::Color getSuccessColor()	{ return sf::Color(0xFF, 0xDE, 0x00); }

		static sf::Color getRedColor()		{ return sf::Color(0xF2, 0x58, 0x3E); }
		static sf::Color getGreenColor()	{ return sf::Color(0x58, 0x70, 0x58); }
		static sf::Color getBlueColor()		{ return sf::Color(0x1E, 0x90, 0xFF); }
		static sf::Color getCyanColor()		{ return sf::Color(0xB0, 0xC4, 0xDE); }
		static sf::Color getWhiteColor()	{ return sf::Color(0xE5, 0xE5, 0xE5); }

		static sf::Color getLockedColor()	{ return sf::Color(0xDD, 0xDD, 0xDD); }
		static sf::Color getLoadingColor()	{ return sf::Color(0xE5, 0xE5, 0xE5); }
	};
}