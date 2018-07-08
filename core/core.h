#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Core
{
	int width;	// Screen width.
	int height; // Screen height.
	
	sf::Clock clock;
	sf::Event event;
	sf::Color color;
	sf::RenderWindow* window;

public:
	bool open;	// State of the window.
	int state;	// State of the game.

	Core(int state = 0);
	Core(int, sf::Color);
	Core(int, sf::Uint8, sf::Uint8, sf::Uint8, sf::Uint8);
	~Core();
	void free();
	void close();

	bool create(const char* title = "", int style = sf::Style::Titlebar | sf::Style::Close);
	bool setIcon(const char* path);

	void clear() const;
	void display() const;

	bool isEvent();
	sf::Event& getEvent();
	sf::RenderWindow*& getWindow();
	const int& getWidth() const;
	const int& getHeight() const;
	double getElapsedTime();
	const sf::Color& getColor() const;
};