#pragma once
#include "eventwindow.h"
#include "colors.h"

namespace cmm
{
	class StaticCore
	{
	protected:
		inline static sf::RenderWindow* window;
		inline static sf::Color color = BACKGROUND_COLOR;
	public:
		inline static bool open = false;	// State of the window.
		explicit StaticCore();
		virtual ~StaticCore();
		static sf::Vector2i getMousePosition();
	};

	class Core /*final*/ : public StaticCore
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
		virtual ~Core() override;
		void free();
		void close();

		virtual bool create(const char* title = "", int style = sf::Style::Titlebar | sf::Style::Close);
		virtual bool setIcon(const char* path);

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