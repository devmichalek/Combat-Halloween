#pragma once
#include "eeentity.h"
#include "text.h"
#include "specs.h"

namespace ee
{
	class KnightBoard
	{

	};

	class Knight final : public Entity
	{
		sf::IntRect rect;

	public:
		Knight();
		~Knight();
		void free();
		void reset();

		bool isModified();
		bool isOneAndOnly() { return true; }
		void setActive(bool active);
		Item getItem();
		virtual bool checkCollision(sf::Vector2i &mouse);

		void load(sf::Vector2f &screen, int amount);
		void handle(const sf::Event &event);
		void draw(sf::RenderWindow* &window, sf::Vector2i &add);
		void mechanics(const double &elapsedTime);

		bool add(Item &data);
		bool remove(sf::Vector2i &mouse);
		bool unfold(sf::Vector2i &mouse);
	};
}