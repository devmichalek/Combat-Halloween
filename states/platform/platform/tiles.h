#pragma once
#include "sprite.h"
#include "eventwindow.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace pla
{

	class Tiles
	{
		int width;
		char wPad, hPad;
		float screen_w;
		float screen_h;

		// --- Test.
		bool collision;
		sf::RectangleShape rect;
		// ---

		int max;
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
		void draw(sf::RenderWindow* &window/*, sf::Shader &shader*/, const float &x, const float &y);
		void read(std::vector<std::string> &vec);

		void switchCollision(bool collision = true);
		bool checkCollisionV(sf::Rect<int> &rect, const float &x, const float &y, const char add = 0); // vertical
		bool checkCollisionH(sf::Rect<int> &rect, const float &x, const float &y, const char add = 0); // horizontal
	};
}