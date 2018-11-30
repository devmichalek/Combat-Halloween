#pragma once
#include "treedefinitions.h"
#include "eeentity.h"
#include "text.h"

namespace ee
{
	struct LandscapeItem final : public Item
	{
		float scale;
		LandscapeItem(int ID = -1, char chosen = 1, float scale = 1.0f);
		~LandscapeItem();
	};

	struct LandscapeBoard
	{
		enum TEXTS
		{
			SCALE = 0,
			SCALE_EDIT,
			GLOBAL,
			GLOBAL_EDIT,
			SIZE
		};

		enum RECTS
		{
			TOP_MINUS = 0,
			BOT_MINUS,
			TOP_PLUS,
			BOT_PLUS
		};

		std::vector<cmm::Text*> texts;
		std::vector<bool> rect_states;
		std::vector<sf::Rect<int>> rects;

		cmm::Sprite board;
		cmm::Sprite plus;
		cmm::Sprite minus;

		void free();
		void load(const float &screen_w, const float &screen_h);
		void draw(sf::RenderWindow* &window);
	};

	struct LandscapeLeaf
	{
		int ID;
		int chosen;
		float scale;
		bool operator==(const LandscapeLeaf &ll) const { return ID == ll.ID; }
	};

	class Landscape final : public Entity
	{
		using LandscapeBox = std::pair<Box, LandscapeLeaf>; // Box + LandscapeLeaf
		using LandscapeTree = bgi::rtree<LandscapeBox, bgi::quadratic<16>>;

		LandscapeItem item;
		LandscapeTree* tree;
		LandscapeBoard board;
		std::vector<LandscapeBox> result;
		
		float minScale;
		float maxScale;
		inline static float globalScale = 0.65f;
		bool modified;

	public:
		Landscape();
		~Landscape();
		void free();	// detroy the tree
		void reset();	// destroy and create the tree

		bool isModified();
		void setActive(bool active = true);
		ee::Item getItem();
		cmm::Sprite* getSprite(const int &chosen);
		bool checkCollision(sf::Vector2i mouse);

		void load(sf::Vector2f &screen, int amount);
		void handle(const sf::Event &event);
		void draw(sf::RenderWindow* &window, sf::Vector2i &add);
		void mechanics(const double &elapsedTime);
		bool add(sf::Vector2i &mouse, const int &ID, const int &chosen, std::string ai = "");
		bool remove(sf::Vector2i &mouse);
		bool unfold(sf::Vector2i &mouse);

	private:

		void setPosition(sf::Vector2i add = sf::Vector2i(0, 0));
		void setTexts();
		void setRects();
	};
}