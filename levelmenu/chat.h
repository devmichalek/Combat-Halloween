#pragma once
#include "sprite.h"
#include "text.h"
#include <vector>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Chat
{
	sf::Color commandColor;
	sf::Color typicalColor;
	float globalYScale;
	float globalYLine;

	float screen_w;
	float screen_h;
	float scale_x;
	float scale_y;

	// The rest basics.
	bool active;
	bool used;

	cmm::Sprite background;

	// Text written.
	cmm::Text username;
	std::vector <cmm::Text*> writtens;
	std::vector <std::string> writtenStrs;

	// Arrow.
	float line;
	float counter;
	cmm::Text arrow;

public:
	Chat();
	~Chat();
	void free();
	void reset();

	void load(float screen_w, float screen_h);
	void handle(sf::Event& event);
	void draw(sf::RenderWindow* &window);
	void mechanics(double elapsedTime);
	void fadeout(float v = 1, int min = 0);

	// Getters.
	bool& isActive();
	bool isCommand();
	bool findCommand(std::string line);
	
	void setWritten();
	void setError();	// Can't find command.

	// Set Colors.
	void setCommandColor(sf::Color newColor);
	void setTypicalColor(sf::Color newColor);
};