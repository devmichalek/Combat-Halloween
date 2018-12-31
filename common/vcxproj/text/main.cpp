#include "core.h"
#include "text.h"
#include "converter.h"
#include <SFML/Graphics/RectangleShape.hpp>

int main(int argc, char** argv)
{
	cmm::Core core(0);
	core.create("Combat Halloween");

	cmm::Text text;
	text.setFont(cmm::JAPOKKI_FONT_PATH);
	text.setText("dap mm");
	// text.fadein(5);
	// text.fadeout(5);
	text.setPosition(core.getWidth() / 2, core.getHeight() / 2);
	text.move(2, 2);
	text.center(core.getWidth() / 2, core.getHeight() / 2);
	text.setScale(1.5, 1.4);
	text.flipHorizontally();
	text.flipVertically();
	text.setSize(30);	printf("Size: %d%s", text.getSize(), cmm::CSNEWLINE);
	text.setRotation(45.0);
	text.setAlpha(MAX_ALPHA);	printf("Alpha: %f%s", text.getAlpha(), cmm::CSNEWLINE);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(3);
	printf("Left: %f=%f%s", text.getX(), text.getLeft(), cmm::CSNEWLINE);
	printf("Right: %f=%f%s", text.getX() + text.getWidth(), text.getRight(), cmm::CSNEWLINE);
	printf("Top: %f=%f%s", text.getY(), text.getTop(), cmm::CSNEWLINE);
	printf("Bot: %f=%f%s", text.getY() + text.getHeight(), text.getBot(), cmm::CSNEWLINE);

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(text.getWidth(), text.getHeight()));
	rect.setPosition(sf::Vector2f(text.getX(), text.getY()));

	while (core.open)
	{
		core.clear();

		while (core.isEvent())
			if (core.getEvent().type == sf::Event::Closed)
				core.open = false;

		core.getWindow()->draw(rect);
		core.getWindow()->draw(text);

		core.getWindow()->display();
	}

	return 0;
}