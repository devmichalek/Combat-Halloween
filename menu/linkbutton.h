#pragma once
#include "button.h"

class LinkButton :public Button
{
	std::string url;

public:
	LinkButton();
	~LinkButton();
	void free();

	void handle(const sf::Event &event);
	void setUrl(std::string newUrl);
	void openWebsite();
};