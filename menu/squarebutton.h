#pragma once
#include "button.h"

class SquareButton :public Button
{
	bool pressed;

public:
	SquareButton();
	~SquareButton();
	void free();

	void handle(const sf::Event &event);
	void setPressed();
	const bool& isPressed() const;
};