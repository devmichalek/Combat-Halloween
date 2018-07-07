#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

namespace cmm
{
	class Sprite
	{
		std::unique_ptr<sf::Sprite> sprite;
		std::unique_ptr<sf::Texture> texture;
		std::vector<sf::IntRect> rects;
		float alpha;

	public:
		const sf::Sprite& get() const;
		void load(const char* path, int numOfOffsets = 1);
		void loadRepeated(const char* path, float w, float h, bool borders = false);
		void create(int w, int h);

		void setColor(sf::Color color);
		sf::Color getColor() const;
		void setAlpha(float alpha = 0);
		float getAlpha() const;

		void fadein(float v = 1, int max = 0xFF);
		void fadeout(float v = 1, int min = 0);

		void flipHorizontally();
		void flipVertically();

		template<class T1, class T2> void setPosition(T1 x, T2 y) { sprite->setPosition(static_cast<float>(x), static_cast<float>(y)); }
		template<class T1, class T2> void move(T1 x, T2 y) { sprite->move(static_cast<float>(x), static_cast<float>(y)); }
		void center(float x, float y);

		template<class T1, class T2> void setOrigin(T1 x, T2 y) { sprite->setOrigin(static_cast<float>(x), static_cast<float>(y)); }
		template<class Type> void setRotation(Type angle) { sprite->setRotation(static_cast<float>(angle)); }
		float getRotation() const;
		template<class T1, class T2> void setScale(T1 x = 1, T2 y = 1) { sprite->setScale(static_cast<float>(x), static_cast<float>(y)); }
		void setOffset(int n);
		unsigned getNumOfOffsets() const;

		const float& getX() const;
		const float& getY() const;
		float getWidth() const;
		float getHeight() const;
		const float& getLeft() const;
		float getRight() const;
		const float& getTop() const;
		const float getBot() const;

		bool checkCollision(float x, float y, float w = 0, float h = 0) const;
		bool checkCollisionRect(sf::Rect <float> rect) const;
		bool checkCollisionCircle(float x, float y) const;
	};
}