#pragma once
#include "text.h"
#include "sound.h"
#include "sprite.h"
#include "thread.h"
#include "eventwindow.h"

namespace lvm
{
	class Board final
	{
		enum Type
		{
			ORYGINAL = 0,
			LOCAL,
			ONLINE,
			SIZE
		};

		enum Icon
		{
			LOCALFILE,
			SERVERFILE,
			CHECKED,
			LEFT,
			RIGHT,
			COUNT
		};

		float screen_w;
		float screen_h;

		cmm::Sound sound;
		std::vector<cmm::Sprite*> iconvec;
		std::vector<std::vector<cmm::Text*>> titlevec;	// Type::SIZE groups with 'n' worlds inside each.
		std::vector<std::vector<cmm::Text*>> detailvec;

		// Thread manipulation / information data.
		cmm::Thread thread;
		std::string msg;
		cmm::Text current_msg;

	public:
		Board();
		~Board();
		void free();
		void load(const float &screen_w, const float &screen_h);
		void draw(sf::RenderWindow* &window);
		void handle(const sf::Event &event);
		void fadein(const float &v, const int &max);
		void fadeout(const float &v, const int &min);

		bool isChosen();
		void setVolume(const float &newVolume);
	};
}
