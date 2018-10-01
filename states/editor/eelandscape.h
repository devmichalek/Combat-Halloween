#pragma once
#pragma warning(disable:4996) //#define _SCL_SECURE_NO_WARNINGS
#include <vector>
#include "eventwindow.h"
#include "treedefinitions.h"
#include "sprite.h"
#include "text.h"

namespace ee // Editor Entity
{
	struct LandscapeEntity // represents a single element
	{
		int id;
		int chosen;
		float scale;

		LandscapeEntity(int newID = -1, int newChosen = 1, float newScale = 1.0f);
		~LandscapeEntity();
		bool operator==(const LandscapeEntity&) const;
	};

	using LandscapeBox = std::pair<Box, LandscapeEntity>;
	
	class Landscape
	{
		float screen_w;
		float screen_h;

		typedef bgi::rtree<LandscapeBox, bgi::quadratic<16>> LandscapeTree;
		LandscapeTree* tree;

		std::vector<LandscapeBox> result;
		LandscapeBox last;

		enum TEXTS
		{
			SCALE = 0,
			SCALE_EDIT,
			GLOBAL,
			GLOBAL_EDIT,
			SIZE
		};
		std::vector<cmm::Text*> texts;

		enum RECTS
		{
			TOP_MINUS = 0,
			BOT_MINUS,
			TOP_PLUS,
			BOT_PLUS
		};
		std::vector<bool> rect_states;
		std::vector<sf::Rect<int>> rects;

		cmm::Sprite board;
		cmm::Sprite plus;
		cmm::Sprite minus;

		inline static float globalScale = 0.65f;
		bool active;
		std::string str;
		float min, max;
		float w, h;

	public:
		Landscape();
		~Landscape();
	private:
		void free();
	public:
		void reset();	// empty the tree

		void init();	// builds tree
		void load(const float &screen_w, const float &screen_h);
		bool handle(const sf::Event &event);	// returns true if it was open
		void draw(sf::RenderWindow* &window, cmm::Sprite* &object, const int &addX, const int &addY);
		void mechanics(const double &elapsedTime);

		const std::vector<LandscapeBox>& get(const int &addX, const int &addY, const float &screen_w, const float &screen_h);
		bool add(const Box &box, const LandscapeEntity &le);
		bool remove(int &mouseX, int &mouseY);
		const int& getLastID();			// get last deleted LandscapeBox's id
		LandscapeBox getLast();

		void setActive(bool newActive = true);
		const bool& isActive() const;
		const int& getChosen();
		void setAI(std::string &ai);
		static float getGlobalScale() { return globalScale; }

	private:
		void setPosition(const int addX = 0, const int addY = 0);	// x y for board
		void setTexts();
		void setRects();
	};
}