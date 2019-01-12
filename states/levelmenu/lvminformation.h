#pragma once
#include "text.h"
#include "sound.h"
#include "sprite.h"
#include "eventwindow.h"

namespace lvm
{
	class Information final
	{
		float screen_w;
		float screen_h;

		enum Types
		{
			ORYGINAL = 0,
			LOCAL,
			ONLINE,
			SIZE
		};

		cmm::Sprite plank;
		cmm::Sprite background;
		cmm::Sprite plankbar;
		int chosen;
		std::vector<cmm::Text*> texts;
		cmm::Sound sound;

	public:
		Information();
		~Information();
		void free();

		void load(const float &screen_w, const float &screen_h);
		void draw(sf::RenderWindow* &window);
		void handle(const sf::Event &event);
		void fadein(const float &v, const int &max);
		void fadeout(const float &v, const int &min);
	private:
		void prepareChosen();
	public:
		void setVolume(const float &newVolume);
		const float getBackgroundAlpha() const;
		const int& getChosen() const;
	};
}
