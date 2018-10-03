#pragma once
#include <SFML/Graphics/Rect.hpp>

namespace ee
{
	class Collision
	{
	protected:
		inline static bool collision = false;
	public:
		virtual bool checkCollision(sf::Rect<int> rect) = 0;

		static void switchCollision() // turn on/off whole collision
		{
			collision = !collision;
		}

		static bool& getCollision()
		{
			return collision;
		}
	};
}