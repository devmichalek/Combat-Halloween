#include "core.h"
#include "text.h"
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
	text.setSize(30);	printf("Size: %d\n", text.getSize());
	text.setRotation(45.0);
	text.setAlpha(MAX_ALPHA);	printf("Alpha: %f\n", text.getAlpha());
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(3);
	printf("Left: %f=%f\n", text.getX(), text.getLeft());
	printf("Right: %f=%f\n", text.getX() + text.getWidth(), text.getRight());
	printf("Top: %f=%f\n", text.getY(), text.getTop());
	printf("Bot: %f=%f\n", text.getY() + text.getHeight(), text.getBot());

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