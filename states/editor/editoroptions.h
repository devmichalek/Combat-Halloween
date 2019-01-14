#pragma once
#include "text.h"
#include "circlebutton.h"
#include <SFML/Graphics/RectangleShape.hpp>

class EditorOptions final
{
	enum LABELS
	{
		// PAGE 1.
		ESCAPE = 0, // CLOSES WINDOW OR ENTITY
		ENTER, // AGREE, YES, OK, APPROVE DECISION
		CTRL_Z, // UNDO
		SPACE, // TEMP QUICK MODE
		LCTRL, // TEMP DELETE MODE
		LSHIFT, // TEMP WHOLE COLLSION MODE

		// PAGE 2.
		A,
		S,
		D,
		Z,
		X,
		C,
		
		// PAGE 3.
		LEFT,
		RIGHT,
		UP,
		DOWN,
		LEFTMOUSE, // PUT OR REMOVE
		RIGHTMOUSE, // UNFOLD
		SCROLLMOUSE,

		AMOUNT
	};

	CircleButton button;
	cmm::Text label;
	cmm::Sprite plank;
	sf::RectangleShape blackLayer;
	cmm::Sprite leftbutton;
	cmm::Sprite rightbutton;

	int first, last;
	std::vector<cmm::Text*> keytextvec;
	std::vector<cmm::Text*> infotextvec;

	int currPage;
	int lastPage;
	cmm::Text pageText;

	bool active;

public:
	EditorOptions();
	~EditorOptions();
private:
	void free();
public:
	void reset();

	void load(const float& screen_w, const float& screen_h);
	void handle(const sf::Event &event);
	void drawButton(sf::RenderWindow* &window);
	void draw(sf::RenderWindow* &window);

	bool isActive() { return active; };

private:
	void setText();
	void setPageText();
	void setBorders();
	bool isAbleToGoLeft();
	bool isAbleToGoRight();
};