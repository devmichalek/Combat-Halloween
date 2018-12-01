#pragma once
#include "text.h"
#include "circlebutton.h"
#include "eakind.h"
#include <SFML/Graphics/RectangleShape.hpp>

class EATools final : public EAKind
{
	int screen_w;
	int screen_h;

	enum TYPES
	{
		DELETEKEY = 0,
		HOTKEY,
		WHOLECOLLISIONKEY,
		COUNT
	};

	std::vector<CircleButton*> buttons;
	std::vector<cmm::Text*> texts;
	std::vector<bool> pressed;
	std::vector<int> states;
	std::vector<int> keys;

	// mark the chosen entity's element
	sf::RectangleShape shape;
	cmm::Sprite checkedIcon;

	// ctrl + z
	bool ctrl_key;
	bool z_key;
	float undoKeyCounter;
	float undoKeyState;

	// support
	bool change;
	bool redBack;

	// hot key
	float hotKeyCounter;
	float hotKeyState;

public:
	EATools();
	~EATools();
	void free();
	void reset();

	void load(const float& screen_w, const float& screen_h);
	void handle(const sf::Event &event, const int &amount);
	void draw(sf::RenderWindow* &window);
	void thumbnail(sf::RenderWindow* &window, std::vector<cmm::Sprite*> &factory, const int& chosen);
	void mechanics(const float &elapsedTime);

	bool isDeleteKeyPressed() const			{ return pressed[DELETEKEY]; }
	bool isHotKeyPressed() const			{ return pressed[HOTKEY] || (states[HOTKEY] && pressed[DELETEKEY]); }
	bool isWholeCollisionKeyPressed() const { return pressed[WHOLECOLLISIONKEY]; }
	bool isHotKeyElapsed();
	bool isUndoKeyElapsed();
	bool isDeleteMode() const				{ return states[DELETEKEY] != 0; }
	bool isChange();
	bool& isRedBack()				{ return redBack; }
	const int& getType() const		{ return type; }
	const int& getChosen() const	{ return chosen; }
};