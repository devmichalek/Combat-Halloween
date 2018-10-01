#pragma once
#include <memory>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace cmm
{
	const char* const JAPOKKI_FONT_PATH = "fonts/Jaapokki-Regular.otf";
	const char* const JCANDLE_FONT_PATH = "fonts/jcandlestickextracond.ttf";

	class Text : public sf::Drawable
	{
		std::unique_ptr<sf::Font> font;
		std::unique_ptr<sf::Text> text;
		float alpha;

	public:
		const std::string getString() const; // cannot return with &
		std::string setFont(const char* path);
		void setText(std::string line);
		void setTextW(std::wstring line);
	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	public:
		void fadein(const float &v, const int &max);
		void fadeout(const float &v, const int &min);

		void flipHorizontally();
		void flipVertically();

		template<class T1, class T2> inline void setPosition(T1 x, T2 y) { text->setPosition(static_cast<float>(x), static_cast<float>(y)); }
		template<class T1, class T2> inline void move(T1 x, T2 y) { text->move(static_cast<float>(x), static_cast<float>(y)); }
		template<class T1, class T2> inline void center(T1 x, T2 y) { text->setPosition(static_cast<float>(x) - getWidth() / 2, static_cast<float>(y) - getHeight() / 2); }

		template<class T1, class T2> inline void setScale(T1 x = 1, T2 y = 1) { text->setScale(static_cast<float>(x), static_cast<float>(y)); }
		template<class Type> inline void setSize(Type size) { text->setCharacterSize(static_cast<int>(size)); }
		int getSize() const;
		template<class Type> inline void setRotation(Type angle) { text->setRotation(static_cast<float>(angle)); }

		void setAlpha(float alpha = 0);
		private: void setRawAlpha(); public:
		const float& getAlpha() const;
		void setFillColor(sf::Color color);
		void setOutlineColor(sf::Color color);
		sf::Color getFillColor() const;
		sf::Color getOutlineColor() const;
		template<class Type> inline void setOutlineThickness(Type thickness) { text->setOutlineThickness(static_cast<float>(thickness)); }

		const float& getX() const;
		const float& getY() const;
		float getWidth() const;
		float getHeight() const;
		const float& getLeft() const;
		float getRight() const;
		const float& getTop() const;
		float getBot() const;

		float getFixedWidth() const;
		float getFixedHeight() const;

		// bool checkCollision(float x, float y, float w = 0, float h = 0) const;
	};
}