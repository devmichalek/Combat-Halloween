// Test of objects: sound, music, text, sprite, request
#include "core.h"
#include "sound.h"
#include "music.h"
#include "text.h"
#include "sprite.h"
#include "request.h"
#include "boost/lexical_cast.hpp"

int main(int argc, char** argv)
{
	if (!strcmp(argv[1], "sound"))
	{
		cmm::Sound sound;
		sound.load("sounds/click.wav");
		cmm::Sound::setGlobalPlayable();
		sound.setVolume(100);
		sound.play();
		while (sound.isPlaying()) {}
	}
	else if (!strcmp(argv[1], "music"))
	{
		cmm::Music music;
		music.load("music/menu.ogg");
		cmm::Music::setGlobalPlayable();
		music.setVolume(100);
		music.play();
		bool state = true;
		float v = static_cast<float>(0.0001);
		while (music.isPlaying())
		{
			if (music.getVolume() == 100)		state = true;
			else if (music.getVolume() == 0)	state = false;
			int v = 1;
			float min = 0.0f, max = 255.0f;
			state ? music.fadeout(v, min) : music.fadein(v, max);
		}
	}
	else if (!strcmp(argv[1], "text"))
	{
		Core core(0);
		core.create("Combat Halloween");

		cmm::Text text;
		text.setFont("fonts/Jaapokki-Regular.otf");
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
		text.setAlpha(0xFF);	printf("Alpha: %f\n", text.getAlpha());
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
		rect.setFillColor(sf::Color(0xFF, 0x00, 0x00, 0x80));

		while (core.open)
		{
			core.clear();

			while (core.isEvent())
				if (core.getEvent().type == sf::Event::Closed)
					core.open = false;

			core.getWindow()->draw(rect);
			core.getWindow()->draw(text.get());

			core.display();
		}
	}
	else if (!strcmp(argv[1], "sprite"))
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
	}

	return 0;
}