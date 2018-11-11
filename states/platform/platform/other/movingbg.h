#pragma once
#include "sprite.h"
#include <SFML/Graphics/RenderTexture.hpp>

namespace pla
{
	class MovingBG final
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
		void draw(sf::RenderTexture &rt);
		void mechanics(const float &elapsedTime, const char &direction);
		const float& getAlpha() const;
	};
}