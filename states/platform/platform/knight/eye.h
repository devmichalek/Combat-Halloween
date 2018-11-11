#pragma once
#include "sprite.h"
#include <SFML/Graphics/RenderTexture.hpp>
//#include "play/game/foe/balloonchat.h"

namespace pla
{
	class Eye final
	{
		float line_y;
		float distance_y;

		float scale_x;

		cmm::Sprite sprite;

		// Texts.
		//Balloonchat balloonchat;
		std::vector<std::string> texts;
		int textWas;
		float textCounter;
		float textLine;

		float viewX, viewY;
		sf::View view;

	public:
		Eye();
		~Eye();
		void free();
		void reset(const sf::Rect<int> &rect);

		void load(const float &screen_w, const float &screen_h);
		void draw(sf::RenderTexture &rt);
		void mechanics(const float &elapsedTime, const sf::Rect<int> &rect, const bool &align);

		const sf::View& getView() const;
		float getViewX();
		float getViewY();
	};
}