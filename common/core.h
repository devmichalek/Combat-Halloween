#pragma once
#include "eventwindow.h"

namespace cmm
{
	class StaticCore
	{
	protected:
		inline static sf::RenderWindow* window;
		inline static sf::Color color = sf::Color(21, 21, 29, 0xFF);
	public:
		inline static bool open = false;	// State of the window.
		StaticCore();
		virtual ~StaticCore();
	};

	class Core : public StaticCore
	{
		float width;	// Screen width.
		float height;	// Screen height.

		sf::Clock clock;
		sf::Event event;

	public:
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
		const sf::Event& getEvent();
		sf::RenderWindow*& getWindow();
		const float& getWidth() const;
		const float& getHeight() const;
		double getElapsedTime();
		const sf::Color& getColor() const;
	};
}