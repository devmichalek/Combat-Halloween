#pragma once
#include "button.h"

class CircleButton final :public Button
{
	bool active;
	bool changed;

public:
	explicit CircleButton();
	~CircleButton() override;
	void free();

	bool handle(const sf::Event &event);
	const bool& isActive() const;
	void setActive(bool active);
	void changeActive();
	bool hasChanged();
	void setChanged(bool changed);
};