#pragma once
#include "eecollision.h"

namespace ee // Editor Entity
{
	class Tile : public Collision
	{
		char** array;

	public:
		Tile();
		~Tile();
	private:
		void free();
	public:
		void reset();	// empty the array

		void init();	// allocate
		char get(const int &x, const int &y);
		bool add(int &mouseX, int &mouseY, const int &chosen);
		int remove(int &mouseX, int &mouseY);
		bool checkCollision(sf::Rect<int> rect);
	};
}