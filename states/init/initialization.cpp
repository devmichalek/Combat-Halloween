#include "initialization.h"
#include "logconsole.h"
#include "loading.h"

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
	state = 0;

	if (!texts.empty())
	{
		for (auto &it : texts)
		{
			delete it;
		}

		texts.clear();
	}

	prev = next = exit = false;
}



void Initialization::load(const float &screen_w, const float &screen_h)
{
	free();

	for (unsigned i = 0; i < AMOUNT; ++i)
		texts.push_back(new cmm::Text);

	// Set font.
	const char* path = cmm::JAPOKKI_FONT_PATH;
	Loading::add(texts[AUTHOR]->setFont(path));
	Loading::add(texts[ASSOCIATION]->setFont(path));
	Loading::add(texts[SEBASTIAN]->setFont(path));
	Loading::add(texts[KAMIL]->setFont(path));
	Loading::add(texts[PRESENTS]->setFont(path));
	Loading::add(texts[HALLOWEEN]->setFont(path));
	Loading::add(texts[COMBAT]->setFont(path));
	if (Loading::isError()) return;

	// Set text.
	texts[AUTHOR]->setTextW(L"Adrian Micha\u0142ek");
	texts[ASSOCIATION]->setText("in alliance with");
	texts[SEBASTIAN]->setText("Sebastian Bialucha");
	texts[KAMIL]->setText("Kamil Gawlik");
	texts[PRESENTS]->setText("presents");
	texts[HALLOWEEN]->setText("Halloween");
	texts[HALLOWEEN]->setOutlineThickness(3);
	texts[COMBAT]->setText("Combat");
	texts[COMBAT]->setOutlineThickness(3);

	// Set size.
	for(unsigned i = 0; i < HALLOWEEN; ++i)
		texts[i]->setSize(screen_h / 24);
	texts[PRESENTS]->setSize(screen_h / 24);
	texts[HALLOWEEN]->setSize(screen_h / 10);
	texts[COMBAT]->setSize(screen_h / 10);

	// Set color.
	texts[AUTHOR]->setFillColor(sf::Color(0xD5, 0xE1, 0xDD));
	texts[ASSOCIATION]->setFillColor(cmm::LogConsole::getWhiteColor());
	texts[SEBASTIAN]->setFillColor(sf::Color(0xD5, 0xE1, 0xDD));
	texts[KAMIL]->setFillColor(sf::Color(0xD5, 0xE1, 0xDD));
	texts[PRESENTS]->setFillColor(cmm::LogConsole::getCyanColor());
	texts[HALLOWEEN]->setFillColor(sf::Color(21, 21, 29));
	texts[HALLOWEEN]->setOutlineColor(cmm::LogConsole::getRedColor());
	texts[COMBAT]->setFillColor(sf::Color(21, 21, 29));
	texts[COMBAT]->setOutlineColor(sf::Color(0xD5, 0xE1, 0xDD));

	// Set position.
	float h = texts[AUTHOR]->getHeight();
	texts[AUTHOR]->center(screen_w / 2, screen_h / 2.5 - screen_h / 20);
	texts[ASSOCIATION]->center(screen_w / 2, texts[AUTHOR]->getBot() + h * 1.5);
	texts[SEBASTIAN]->center(screen_w / 2, texts[ASSOCIATION]->getBot() + h * 1.5);
	texts[KAMIL]->center(screen_w / 2, texts[SEBASTIAN]->getBot() + h);
	texts[PRESENTS]->setPosition(screen_w / 2 - texts[PRESENTS]->getWidth() / 2, texts[KAMIL]->getBot() + h);
	texts[COMBAT]->center(screen_w / 2 - texts[HALLOWEEN]->getWidth() / 2 - screen_h / 32 - screen_h / 144, screen_h / 2 - screen_h / 20);
	texts[HALLOWEEN]->setPosition(texts[COMBAT]->getRight() + screen_h / 72 + screen_h / 16, texts[COMBAT]->getBot() - texts[HALLOWEEN]->getHeight());
}

void Initialization::draw(sf::RenderWindow* &window)
{
	if (!next)
	{
		for(auto &it : texts)
			window->draw(it->get());
	}
}

void Initialization::mechanics(const double &elapsedTime)
{
	if (!next)
	{
		int min = 0, max = 0xFF;

		float velocity = static_cast<float>(elapsedTime) * 0xFF;
		if (state == 0)
		{
			texts[AUTHOR]->fadein(velocity, max);
		}
		else if (state == 1)
		{
			texts[ASSOCIATION]->fadein(velocity * (float)1.5, max);
			texts[SEBASTIAN]->fadein(velocity * (float)1.5, max);
			texts[KAMIL]->fadein(velocity * (float)1.5, max);
		}
		else if (state == 2)
		{
			texts[PRESENTS]->fadein(velocity * (float)1.5, max);
		}
		else if (state == 3)
		{
			texts[AUTHOR]->fadeout(velocity / 2, min);
			texts[ASSOCIATION]->fadeout(velocity / 2, min);
			texts[SEBASTIAN]->fadeout(velocity / 2, min);
			texts[KAMIL]->fadeout(velocity / 2, min);
			texts[PRESENTS]->fadeout(velocity / 2, min);
		}
		else if (state == 4)
		{
			texts[COMBAT]->fadein(velocity, max);
		}
		else if (state == 5)
		{
			texts[HALLOWEEN]->fadein(velocity, max);
		}
		else if (state == 6)
		{
			texts[COMBAT]->fadeout(velocity, min);
			texts[HALLOWEEN]->fadeout(velocity, min);
		}

		// 1
		if (texts[AUTHOR]->getAlpha() == 0xFF && state == 0)
		{
			state = 1;
		}
		else if (texts[ASSOCIATION]->getAlpha() == 0xFF && state == 1)
		{
			state = 2;
		}
		else if (texts[PRESENTS]->getAlpha() == 0xFF && state == 2)
		{
			state = 3;
		}
		else if (texts[PRESENTS]->getAlpha() == 0 && state == 3)
		{
			state = 4;
		}

		// 2
		else if (texts[COMBAT]->getAlpha() == 0xFF && state == 4)
		{
			state = 5;
		}
		else if (texts[HALLOWEEN]->getAlpha() == 0xFF && state == 5)
		{
			state = 6;
		}
		else if (texts[HALLOWEEN]->getAlpha() == 0 && state == 6)
		{
			next = true;
		}
	}
}



bool Initialization::isReady() const
{
	return next;
}

void Initialization::setState(int &state)
{
	if (isReady())
	{
		state = cmm::LOGIN;
	}
}