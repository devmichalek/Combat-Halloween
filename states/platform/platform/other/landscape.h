#pragma once
#include "eventwindow.h"
#include "treedefinitions.h"
#include "sprite.h"

namespace pla // platform
{
	struct LandscapeUnit final
	{
		char chosen;
		float scale;

		LandscapeUnit(char newChosen = 1, float newScale = 1.0f);
		virtual ~LandscapeUnit();
		virtual bool operator==(const LandscapeUnit &lu) const
		{
			if (chosen == lu.chosen && scale == lu.scale)
				return true;
			return false;
		}
	};

	class Landscape final
	{
		float screen_w;
		float screen_h;

		using LandscapeBox = std::pair<Box, LandscapeUnit>;
		typedef bgi::rtree<LandscapeBox, bgi::quadratic<16>> LandscapeTree;
		LandscapeTree* tree;

		std::vector<LandscapeBox> result;
		std::vector<cmm::Sprite*> sprites;

	public:
		Landscape();
		~Landscape();
	private:
		void free();
	public:
		void reset();	// empty the tree

		void init();	// builds tree
		void load(const float &screen_w, const float &screen_h);
		void draw(sf::RenderWindow* &window/*, sf::Shader &shader*/, const float &x, const float &y);
		void read(std::vector<std::string> &vec);
	};
}