#pragma once
#include "button.h"

class SquareButton final :public Button
{
	bool pressed;

public:
	explicit SquareButton();
	~SquareButton() override;
	void free();

	void handle(const sf::Event &event);
	void setPressed();
	const bool& isPressed() const;
};