#pragma once
#include "kind.h"
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include "converter.h"

namespace ee
{
	struct Item : public cmm::Kind
	{
		int ID;
		int chosen;
		int type;
		std::string ai; // additional information
		sf::Vector2i position;

		Item(const Item &item)
		{
			ID = item.ID;
			chosen = item.chosen;
			type = item.type;
			ai = item.ai;
			position = item.position;
		}

		Item(int ID, int type, int chosen, sf::Vector2i position, std::string ai = cmm::SEMPTY)
		{
			this->ID = ID;
			this->chosen = chosen;
			this->type = type;
			this->ai = ai;
			this->position = position;
		}

		Item()		{ free(); }
		~Item()		{ free(); }
		void free() { reset(); }

		void reset()
		{
			ID = chosen = type = -1;
			ai = cmm::SEMPTY;
			position = sf::Vector2i(-1, -1);
		}
	};
}