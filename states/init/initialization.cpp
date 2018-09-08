#include "initialization.h"

Initialization::Initialization()
{
	free();
}

Initialization::~Initialization()
{
	free();
}

void Initialization::free()
{
	ready = false;
	state = 0;

	if (!texts.empty())
	{
		for (auto &it : texts)
		{
			delete it;
		}

		texts.clear();
	}
}



void Initialization::load(const float &screen_w, const float &screen_h)
{
	free();

	for (unsigned i = 0; i < AMOUNT; i++)
	{
		texts.push_back(new cmm::Text);
	}

	// Set font.
	const char* path = "fonts/Jaapokki-Regular.otf";
	texts[AUTHOR]->setFont(path);
	texts[PRESENTS]->setFont(path);
	texts[HALLOWEEN]->setFont(path);
	texts[COMBAT]->setFont(path);

	// Set text.
	texts[AUTHOR]->setTextW(L"Adrian Micha\u0142ek");
	texts[PRESENTS]->setText("presents");
	texts[HALLOWEEN]->setText("Halloween");
	texts[HALLOWEEN]->setOutlineThickness(3);
	texts[COMBAT]->setText("Combat");
	texts[COMBAT]->setOutlineThickness(3);

	// Set size.
	texts[AUTHOR]->setSize(screen_h / 24);
	texts[PRESENTS]->setSize(screen_h / 24);
	texts[HALLOWEEN]->setSize(screen_h / 10);
	texts[COMBAT]->setSize(screen_h / 10);

	// Set color.
	texts[AUTHOR]->setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
	texts[PRESENTS]->setFillColor(sf::Color(0xB0, 0xC4, 0xDE));
	texts[HALLOWEEN]->setFillColor(sf::Color(21, 21, 29));
	texts[HALLOWEEN]->setOutlineColor(sf::Color(0xF2, 0x58, 0x3E));
	texts[COMBAT]->setFillColor(sf::Color(21, 21, 29));
	texts[COMBAT]->setOutlineColor(sf::Color(0xD5, 0xE1, 0xDD));


	// Set position.
	texts[AUTHOR]->center(screen_w / 2, screen_h / 2 - screen_h / 20);
	texts[PRESENTS]->setPosition(screen_w / 2 - texts[PRESENTS]->getWidth() / 2, texts[AUTHOR]->getBot());
	texts[COMBAT]->center(screen_w / 2 - texts[HALLOWEEN]->getWidth() / 2 - screen_h / 32 - screen_h / 144, screen_h / 2 - screen_h / 20);
	texts[HALLOWEEN]->setPosition(texts[COMBAT]->getRight() + screen_h / 72 + screen_h / 16, texts[COMBAT]->getBot() - texts[HALLOWEEN]->getHeight());
}

void Initialization::draw(sf::RenderWindow* &window)
{
	if (!ready)
	{
		window->draw(texts[AUTHOR]->get());
		window->draw(texts[PRESENTS]->get());
		window->draw(texts[COMBAT]->get());
		window->draw(texts[HALLOWEEN]->get());
	}
}

void Initialization::mechanics(const double &elapsedTime)
{
	if (!ready)
	{
		int min = 0, max = 0xFF;

		float velocity = static_cast<float>(elapsedTime) * 0xFF;
		if (state == 0)
		{
			texts[AUTHOR]->fadein(velocity, max);
		}
		else if (state == 1)
		{
			texts[PRESENTS]->fadein(velocity * (float)1.5, max);
		}
		else if (state == 2)
		{
			texts[AUTHOR]->fadeout(velocity, min);
			texts[PRESENTS]->fadeout(velocity, min);
		}
		else if (state == 3)
		{
			texts[COMBAT]->fadein(velocity, max);
		}
		else if (state == 4)
		{
			texts[HALLOWEEN]->fadein(velocity, max);
		}
		else if (state == 5)
		{
			texts[COMBAT]->fadeout(velocity, min);
			texts[HALLOWEEN]->fadeout(velocity, min);
		}

		// 1
		if (texts[AUTHOR]->getAlpha() == 0xFF && state == 0)
		{
			state = 1;
		}
		else if (texts[PRESENTS]->getAlpha() == 0xFF && state == 1)
		{
			state = 2;
		}
		else if (texts[PRESENTS]->getAlpha() == 0 && state == 2)
		{
			state = 3;
		}

		// 2
		else if (texts[COMBAT]->getAlpha() == 0xFF && state == 3)
		{
			state = 4;
		}
		else if (texts[HALLOWEEN]->getAlpha() == 0xFF && state == 4)
		{
			state = 5;
		}
		else if (texts[HALLOWEEN]->getAlpha() == 0 && state == 5)
		{
			ready = true;
		}
	}
}



const bool& Initialization::isNext() const
{
	return ready;
}
