#include "core.h"

cmm::Core::Core(int state)
{
	open = false;
	this->state = state;
	width = 0;
	height = 0;
	color = sf::Color::Black;
	window = nullptr;
}

cmm::Core::Core(int state, sf::Color color)
{
	open = false;
	this->state = state;
	width = 0;
	height = 0;
	this->color = color;
	window = nullptr;
}

cmm::Core::Core(int state, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 A)
{
	open = false;
	this->state = state;
	width = 0;
	height = 0;
	this->color = sf::Color(R, G, B, A);
	window = nullptr;
}

cmm::Core::~Core()
{
	free();
}

void cmm::Core::free()
{
	close();
	state = 0;
	color = sf::Color::Black;
}

void cmm::Core::close()
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



bool cmm::Core::create(const char* title, int style)
{
	// Make sure window is destroyed.
	close();

	// Find correct window size.
	width = sf::VideoMode::getDesktopMode().width / 1.2f;
	if (width > 2560)
		width = 2560;
	else if (width < 900)
		return false;
	height = width * 0.5625f;

	// Create window.
	window = new sf::RenderWindow(sf::VideoMode((int)width, (int)height), title, style);
	if (!window)
	{
		return false;
	}

	open = true;
	return true;
}

bool cmm::Core::setIcon(const char* path)
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



void cmm::Core::clear() const
{
	window->clear(color);
}

void cmm::Core::display() const
{
	window->display();
}



bool cmm::Core::isEvent()
{
	return window->pollEvent(event);
}

const sf::Event& cmm::Core::getEvent()
{
	return event;
}

sf::RenderWindow*& cmm::Core::getWindow()
{
	return window;
}

const float& cmm::Core::getWidth() const
{
	return width;
}

const float& cmm::Core::getHeight() const
{
	return height;
}

double cmm::Core::getElapsedTime()
{
	const double elapsedTime = static_cast <double> (clock.getElapsedTime().asMicroseconds()) / 1000000; // per sec
	clock.restart();

	return elapsedTime;
}

const sf::Color& cmm::Core::getColor() const
{
	return color;
}