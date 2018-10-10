#include "levelmenuinformation.h"
#include "loading.h"

LevelMenuInformation::LevelMenuInformation()
{
	free();
}

LevelMenuInformation::~LevelMenuInformation()
{
	free();
}

void LevelMenuInformation::free()
{
	for (auto &it : texts)
	{
		delete it;
		it = nullptr;
	}

	chosen = -1;
}

void LevelMenuInformation::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	Loading::add(plank.load("images/other/splank.png"));
	if (Loading::isError())	return;
	plank.setScale(screen_w / 5120, screen_h / 2880);

	Loading::add(background.loadRepeated("images/other/sayagata.png", screen_w * 1.5f, screen_h * 1.5f, true));
	if (Loading::isError())	return;
	background.setScale(0.75, 0.75);

	Loading::add(plankbar.loadRepeated("images/other/plankbar.png", screen_w * 1.5f, screen_h / 18.0f, true));
	if (Loading::isError())	return;
	plankbar.setScale(0.75, 0.5);

	for (unsigned i = 0; i < SIZE; ++i)
	{
		texts.push_back(new cmm::Text);
		Loading::add(texts[i]->setFont(cmm::JCANDLE_FONT_PATH));
		if (Loading::isError())	return;
		texts[i]->setSize(screen_h / 16);
		texts[i]->setFillColor(cmm::LOCKED_COLOR);
	}

	chosen = 0;
	texts[MAIN]->setText("Main");
	texts[MINE]->setText("Local");
	texts[BYUSERS]->setText("Online");
	texts[MAIN]->setPosition(screen_w / 8, screen_h / 7);
	texts[MINE]->setPosition(texts[MAIN]->getRight() + screen_w / 20, texts[MAIN]->getTop());
	texts[BYUSERS]->setPosition(texts[MINE]->getRight() + screen_w / 20, texts[MAIN]->getTop());

	plankbar.setPosition(0, texts[MINE]->getBot() + screen_h / 72);

	Loading::add(sound.load("sounds/click.wav"));
	if (Loading::isError())	return;

	prepareChosen();
}

void LevelMenuInformation::draw(sf::RenderWindow* &window)
{
	window->draw(background);
	for (int i = texts.size() - 1; i >= 0 ; --i)
	{
		if (chosen == i) continue;
		plank.setPosition(texts[i]->getX() + texts[i]->getWidth()/2 - plank.getWidth()/2, texts[i]->getY());
		window->draw(plank);
		window->draw(*texts[i]);
	}

	plank.setPosition(texts[chosen]->getX() + texts[chosen]->getWidth() / 2 - plank.getWidth() / 2, texts[chosen]->getY());
	window->draw(plank);
	window->draw(*texts[chosen]);

	window->draw(plankbar);
}

void LevelMenuInformation::handle(const sf::Event &event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			for (int i = 0; i < (int)texts.size(); ++i)
			{
				if (i == chosen) continue;
				plank.setPosition(texts[i]->getX() + texts[i]->getWidth() / 2 - plank.getWidth() / 2, texts[i]->getY());
				if (plank.checkCollision((float)event.mouseButton.x, (float)event.mouseButton.y))
				{
					sound.play();
					chosen = i;
					prepareChosen();
					break;
				}
			}
		}
	}
}

void LevelMenuInformation::fadein(const float &v, const int &max)
{
	plank.fadein(v, max);
	background.fadein(v, max);
	plankbar.fadein(v, max);
	for (auto &it : texts)
	{
		it->fadein(v, max);
	}
}

void LevelMenuInformation::fadeout(const float &v, const int &min)
{
	plank.fadeout(v, min);
	background.fadeout(v, min);
	plankbar.fadeout(v, min);
	for (auto &it : texts)
	{
		it->fadeout(v, min);
	}
}

void LevelMenuInformation::prepareChosen()
{
	for (auto &it : texts)
	{
		it->setFillColor(cmm::LOCKED_COLOR);
		it->setPosition(it->getX(), screen_h / 7);
	}

	texts[chosen]->setFillColor(cmm::LOADING_COLOR);
	texts[chosen]->move(0, -screen_h / 144);
}





void LevelMenuInformation::setVolume(const float &newVolume)
{
	sound.setVolume(newVolume);
}

const float LevelMenuInformation::getBackgroundAlpha() const
{
	return background.getAlpha();
}

const int& LevelMenuInformation::getChosen() const
{
	return chosen;
}