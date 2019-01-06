#pragma once
#include <SFML/Graphics/RenderTexture.hpp>
#include "sprite.h"

namespace pla
{
	class ExitDoor final
	{
		float screen_w;
		float screen_h;

		std::vector<cmm::Sprite*> bg;
		cmm::Sprite door;
		sf::Vector2f reference;

	public:
		ExitDoor();
		~ExitDoor();
	private:
		void free();
	public:

		void load(const float &screen_w, const float &screen_h);
		void draw(sf::RenderTexture &rt, const float &x, const float &y);
		void read(std::string &str);

		// Knight's interaction functions:

		// Other
	private:
		void position(const float &x, const float &y);
	};
}