#pragma once
#define _SCL_SECURE_NO_WARNINGS
#include <vector>
#include "treedefinitions.h"
#include "sprite.h"
#include "text.h"

namespace ee // Editor Entity
{
	struct LandscapeEntity
	{
		int id;
		int chosen;
		sf::Vector2f scale;
		LandscapeEntity(int newID, int newChosen, sf::Vector2f newScale) : id(newID), chosen(newChosen), scale(newScale) {}
		bool operator==(const LandscapeEntity &le) const
		{
			return id == le.id;
		}
	};

	//using LandscapePair = std::pair<int, int>;	// chosen + ID
	using LandscapeBox = std::pair<Box, LandscapeEntity>;
	
	class Landscape
	{
		typedef bgi::rtree<LandscapeBox, bgi::quadratic<16>> LandscapeTree;

		int count;
		int lastID;
		LandscapeTree* tree;
		std::vector<LandscapeBox> result;

	public:
		Landscape();
		~Landscape();
	private:
		void free();
	public:
		void reset();	// empty the tree

		void init();	// builds tree
		const std::vector<LandscapeBox>& get(const int &addX, const int &addY, const float &screen_w, const float &screen_h);
		bool add(const Box &box, const LandscapeEntity &le);
		bool remove(int &mouseX, int &mouseY);
		int getID();
	};
}

namespace ed // Editor Deck
{
	class Landscape
	{
		cmm::Sprite board;
		cmm::Sprite plus;
		cmm::Sprite minus;
		cmm::Text scaleTextForm;
		cmm::Text scaleText;

		bool active;
		int target;
		float min, max;

		std::vector<int> ids;
	public:
		Landscape();
		~Landscape();
	private:
		void free();
	public:
		void reset();

		void load(const float &screen_w, const float &screen_h);
		void handle(const sf::Event &event);
		void draw(sf::RenderWindow* &window);

		int getTarget(); // returns id
		std::string getNewString();
	};
}