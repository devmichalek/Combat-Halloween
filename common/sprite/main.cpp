#include "core.h"
#include "sprite.h"

int main(int argc, char** argv)
{
	Core core(0, sf::Color::White);
	core.create("Combat Halloween");

	cmm::Sprite sprite;
	sprite.load("images/buttons/agree.png", 3);
	sprite.setAlpha(0xFF);
	sprite.setPosition(100, 100);
	sprite.setColor(sf::Color::Red);

	bool state = true;
	// int offset = 0;
	// int limit = boost::lexical_cast<int>(argv[3]);
	while (core.open)
	{
		core.clear();

		while (core.isEvent())
			if (core.getEvent().type == sf::Event::Closed)
				core.open = false;

		core.getWindow()->draw(sprite.get());

		if (sprite.getAlpha() == 0xFF)		state = true;
		else if (sprite.getAlpha() == 0)	state = false;
		int v = 1;
		float min = 0.0f, max = 255.0f;
		state ? sprite.fadeout(v, min) : sprite.fadein(v, max);
		//sprite.setOffset(offset);
		//offset == limit - 1 ? offset = 0 : ++offset;
		core.display();
	}

	return 0;
}