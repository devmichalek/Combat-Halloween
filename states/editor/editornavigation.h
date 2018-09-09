#pragma once
#include "text.h"
#include "circlebutton.h"

class EditorNavigation
{
	enum KIND
	{
		MENU = 0,
		LEVELMENU,
		PLAY,
		SIZE
	};

	cmm::Sprite background;
	std::vector<CircleButton*> buttons;
	std::vector<cmm::Text*> labels;

public:
	EditorNavigation();
	~EditorNavigation();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void drawBG(sf::RenderWindow* &window);

	void setVolume(const float &volume);

	// Enabling states directly.
	void setHome();
	void setLevelMenu();
	void setPlay();

	const bool& isHome() const;
	const bool& isLevelMenu() const;
	const bool& isPlay() const;
};