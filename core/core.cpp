#include "core.h"

Core::Core(int state)
{
	open = false;
	this->state = state;
	width = 0;
	height = 0;
	color = sf::Color::Black;
	window = nullptr;
}

Core::Core(int state, sf::Color color)
{
	open = false;
	this->state = state;
	width = 0;
	height = 0;
	this->color = color;
	window = nullptr;
}

Core::Core(int state, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 A)
{
	open = false;
	this->state = state;
	width = 0;
	height = 0;
	this->color = sf::Color(R, G, B, A);
	window = nullptr;
}

Core::~Core()
{
	free();
}

void Core::free()
{
	close();
	state = 0;
	color = sf::Color::Black;
}

void Core::close()
{
	if (window)
	{
		window->close();
		delete window;
		window = nullptr;
	}

	width = 0;
	height = 0;
	open = false;
}



bool Core::create(const char* title, int style)
{
	// Make sure window is destroyed.
	close();

	// Find correct window size.
	width = static_cast<int>(sf::VideoMode::getDesktopMode().width / 1.2);
	if (width > 2560)
		width = 2560;
	else if (width < 900)
		return false;
	height = static_cast<int>(width *0.5625);

	// Create window.
	window = new sf::RenderWindow(sf::VideoMode(width, height), title, style);
	if (!window)
	{
		return false;
	}

	open = true;
	return true;
}

bool Core::setIcon(const char* path)
{
	if (window)
	{
		sf::Image icon;
		if (icon.loadFromFile(path))
		{
			window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
			return true;
		}
	}

	return false;
}



void Core::clear() const
{
	window->clear(color);
}

void Core::display() const
{
	window->display();
}



bool Core::isEvent()
{
	return window->pollEvent(event);
}

sf::Event& Core::getEvent()
{
	return event;
}

sf::RenderWindow*& Core::getWindow()
{
	return window;
}

const int& Core::getWidth() const
{
	return width;
}

const int& Core::getHeight() const
{
	return height;
}

double Core::getElapsedTime()
{
	const double elapsedTime = static_cast <double> (clock.getElapsedTime().asMicroseconds()) / 1000000; // per sec
	clock.restart();

	return elapsedTime;
}

const sf::Color& Core::getColor() const
{
	return color;
}