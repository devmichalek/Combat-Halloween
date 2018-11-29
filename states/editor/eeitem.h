#pragma once
#include "kind.h"
#include <string>
#include <SFML/Graphics/Rect.hpp>

namespace ee
{
	struct Item : public cmm::Kind
	{
		int ID;
		int chosen;
		int type;
		std::string ai; // additional information
		sf::Vector2i position;

		Item()		{ free(); }
		~Item()		{ free(); }
		void free() { reset(); }
		void reset()
		{
			ID = chosen = type = -1;
			ai = "";
			position = sf::Vector2i(-1, -1);
		}
	};
}