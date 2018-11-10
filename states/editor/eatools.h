#pragma once
#include "text.h"
#include "circlebutton.h"

class EATools final
{
	int screen_w;
	int screen_h;

	enum TYPES
	{
		DELETEKEY = 0,
		HOTKEY,
		COLLISIONKEY,
		COUNT
	};

	std::vector<CircleButton*> buttons;
	std::vector<cmm::Text*> texts;
	std::vector<bool> pressed;
	std::vector<int> states;
	std::vector<int> keys;

	cmm::Sprite checkedIcon;

	float hotKeyCounter;
	float hotKeyState;

public:
	EATools();
	~EATools();
private:
	void free();
public:
	void reset();
	void resetButtons();

	void load(const float& screen_w, const float& screen_h);
	bool handle(const sf::Event &event);
	void drawTools(sf::RenderWindow* &window);
	void draw(sf::RenderWindow* &window, std::vector<cmm::Sprite*> &sprites, const int& chosen);
	void mechanics(const float &elapsedTime);

	bool isDeleteKeyPressed();
	bool isHotKeyPressed();
	bool isCollisionKeyPressed();

	bool isHotKeyElapsed();
	bool isDeleteMode() const;
};