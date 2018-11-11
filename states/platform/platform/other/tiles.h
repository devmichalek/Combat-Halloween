#pragma once
#include "sprite.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "definitions.h"

namespace pla
{
	class Tiles final
	{
		char wPad, hPad;
		float screen_w;
		float screen_h;

#ifdef __TEST__
		bool collision;
		sf::RectangleShape rect;
#endif
		sf::Vector2i last;
		char** tiles;
		char** untiles;	// unvisible tiles
		std::vector <cmm::Sprite*> sprites;

	public:
		Tiles();
		~Tiles();
	private:
		void free();
	public:
		void reset();
		void load(const float &screen_w, const float &screen_h);
		void draw(sf::RenderTexture &rt, const float &x, const float &y);
		void read(std::vector<std::string> &vec);

#ifdef __TEST__
		void switchCollision(bool collision = true);
#endif
		bool checkCollisionV(sf::Rect<int> &rect, const float &x, const float &y, const char add = 0); // vertical
		bool checkCollisionH(sf::Rect<int> &rect, const float &x, const float &y, const char add = 0); // horizontal

		// get last 
		float getTop();
		float getLeft();
	};
}