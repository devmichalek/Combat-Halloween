#pragma once
#include "text.h"
#include "sound.h"
#include "sprite.h"
#include <vector>
#include "eventwindow.h"

class LevelMenuInformation final
{
	float screen_w;
	float screen_h;

	enum Types
	{
		ORYGINAL = 0,
		MINE,
		BYUSERS,
		SIZE
	};

	cmm::Sprite plank;
	cmm::Sprite background;
	cmm::Sprite plankbar;
	int chosen;
	std::vector<cmm::Text*> texts;
	cmm::Sound sound;

public:
	LevelMenuInformation();
	~LevelMenuInformation();
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