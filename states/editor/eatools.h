#pragma once
#include "text.h"
#include "circlebutton.h"

class EATools
{
	int screen_w, screen_h;

	cmm::Sprite checkedIcon;

	// Deleting Mode
	char deleteMode;	// 0 = no delete mode, 1 - temporary (ctrl), 2 - pernament (button)
	bool deleteKeyPressed;
	bool hotKeyPressed;
	CircleButton deleteButton;
	cmm::Text deleteText;

	float hotKeyCounter;
	float hotKeyState;

public:
	EATools();
	~EATools();
private:
	void free();
public:
	void reset();

	void load(const float& screen_w, const float& screen_h);
	bool handle(const sf::Event &event);
	void drawTools(sf::RenderWindow* &window);
	void draw(sf::RenderWindow* &window, std::vector<cmm::Sprite*> &sprites, const int& chosen);
	void mechanics(const float &elapsedTime);

	const bool& isDeleteKeyPressed() const;
	const bool& isHotKeyPressed() const;
	bool isHotKeyElapsed();
	bool isDeleteMode() const;
	void resetDeleteMode();
};