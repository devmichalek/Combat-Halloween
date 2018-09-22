#pragma once
#include <SFML/Graphics/Rect.hpp>

namespace ee // Editor Entity
{
	class Knight
	{
		int ID;
		sf::IntRect rect;
	public:
		Knight();
		~Knight();
	private:
		void free();
	public:
		void reset();

		void init(const int& w, const int& h);
		bool add(const int& x, const int& y, const int& newID);
		bool remove(int& x, int y);
		sf::Vector2f get();	// pos x y
		bool isSet();
		const int& getID() const;
	};
}