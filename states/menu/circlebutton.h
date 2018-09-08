#pragma once
#include "button.h"

class Circlebutton :public Button
{
	bool active;
	bool changed;

public:
	Circlebutton();
	~Circlebutton();
	void free();

	bool handle(const sf::Event &event);
	const bool& isActive() const;
	void setActive(bool active);
	void changeActive();
	bool hasChanged();
	void setChanged(bool changed);
};