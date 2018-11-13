#pragma once
#include "button.h"

class LinkButton final :public Button
{
	std::string url;

public:
	explicit LinkButton();
	~LinkButton() override;
	void free();

	void handle(const sf::Event &event);
	void setUrl(std::string newUrl);
	void openWebsite();
};