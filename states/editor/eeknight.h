#pragma once
#include "eeentity.h"
#include "text.h"
#include "specs.h"

namespace ee
{
	struct KnightBoard : public cmm::Specs
	{
		cmm::Text claimer; // Use user's specification.
		sf::IntRect rclaimer;
		bool sclaimer;

		std::vector<int> mins;
		std::vector<int> maxs;
		std::vector<float> values;
		std::vector<float> ratios;
		std::vector<bool> states;
		std::vector<sf::Rect<int>> rects;
		std::vector<cmm::Text*> texts;

		cmm::Sprite board;
		cmm::Sprite plus;
		cmm::Sprite minus;

		KnightBoard();
		~KnightBoard();
		void free();
		void load(sf::Vector2f &screen);
		void draw(sf::RenderWindow* &window);
	};

	class Knight final : public Entity
	{
		bool modified;
		sf::IntRect rect;
		KnightBoard board;

	public:
		Knight();
		~Knight();
		void free();
		void reset();

		bool isModified();
		bool isOneAndOnly() { return true; }

		Item getItem();
		virtual bool checkCollision(sf::Vector2i &mouse);

		void load(sf::Vector2f &screen, int amount);
		void handle(const sf::Event &event);
		void draw(sf::RenderWindow* &window, sf::Vector2i &add);
		void mechanics(const double &elapsedTime);

		bool add(Item &data);
		bool remove(sf::Vector2i &mouse);
		bool unfold(sf::Vector2i &mouse);

	private: // Board
		void setPosition(sf::Vector2i add = sf::Vector2i(0, 0));
		void setTexts();
		void setRects();
	};
}