#include "editornavigation.h"
#include "loading.h"

EditorNavigation::EditorNavigation()
{
	free();
}

EditorNavigation::~EditorNavigation()
{
	free();
}

void EditorNavigation::free()
{
	if (!buttons.empty())
	{
		for (auto &it : buttons)
		{
			delete it;
			it = nullptr;
		}

		buttons.clear();
	}

	if (!labels.empty())
	{
		for (auto &it : labels)
		{
			delete it;
			it = nullptr;
		}

		labels.clear();
	}
}

void EditorNavigation::reset()
{
	for (auto &it : buttons)
	{
		it->setActive(false);
	}
}


void EditorNavigation::load(const float &screen_w, const float &screen_h)
{
	float scale_x = screen_w / 2560;
	float scale_y = screen_h / 1440;

	// BG
	Loading::add(background.load("images/platform/background/full.png"));
	if (Loading::isError())	return;
	background.setScale(scale_x, scale_y);

	for (int i = 0; i < KIND::SIZE; ++i)
	{
		buttons.push_back(new CircleButton);
		labels.push_back(new cmm::Text);
	}
	
	buttons[MENU]->load("images/buttons/home.png");
	buttons[LEVELMENU]->load("images/buttons/levelmenu.png");
	buttons[PLAY]->load("images/buttons/play.png");
	if (Loading::isError())	return;

	for(auto &it : buttons)
		it->setScale(scale_x, scale_y);

	buttons[MENU]->setPosition(screen_w / 256, screen_h / 144);
	buttons[LEVELMENU]->setPosition(buttons[MENU]->getRight() + screen_w / 256, screen_h / 144);
	buttons[PLAY]->setPosition(screen_w - screen_w / 256 - buttons[PLAY]->getWidth(), screen_h / 144);

	setVolume(0.0f); // muted

	std::string pathToFont = cmm::JCANDLE_FONT_PATH;
	for (auto &it : labels)
	{
		it->setFont(pathToFont.c_str());
		it->setSize(screen_w / 60);
		it->setAlpha(0xFF);
		it->setFillColor(sf::Color::White);
	}

	labels[MENU]->setText("Menu");
	labels[LEVELMENU]->setText("Level Menu");
	labels[PLAY]->setText("Test");

	for (int i = 0; i < KIND::SIZE; ++i)
		labels[i]->setPosition(buttons[i]->getLeft() + buttons[i]->getWidth() / 2 - labels[i]->getWidth() / 2, buttons[i]->getBot() + screen_w / 300.0f);
}



void EditorNavigation::handle(const sf::Event &event)
{
	for (auto &it : buttons)
		it->handle(event);
}

void EditorNavigation::draw(sf::RenderWindow* &window)
{
	for (auto &it : buttons)
		it->draw(window);

	for (auto &it : labels)
		window->draw(it->get());
}

void EditorNavigation::drawBG(sf::RenderWindow* &window)
{
	window->draw(background.get());
}



void EditorNavigation::setVolume(const float &volume)
{
	for (auto &it : buttons)
		it->setVolume(volume);
}

void EditorNavigation::setHome()
{
	buttons[MENU]->setActive(true);
}

void EditorNavigation::setLevelMenu()
{
	buttons[LEVELMENU]->setActive(true);
}

void EditorNavigation::setPlay()
{
	buttons[PLAY]->setActive(true);
}

const bool& EditorNavigation::isHome() const
{
	return buttons[MENU]->isActive();
}

const bool& EditorNavigation::isLevelMenu() const
{
	return buttons[LEVELMENU]->isActive();
}

const bool& EditorNavigation::isPlay() const
{
	return buttons[PLAY]->isActive();
}