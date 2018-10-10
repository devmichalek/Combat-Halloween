#include "eatools.h"
#include "loading.h"
#include "eecollision.h"

EATools::EATools()
{
	free();
}

EATools::~EATools()
{
	free();
}

void EATools::free()
{
	screen_w = 0;
	screen_h = 0;

	if (!buttons.empty())
	{
		for (auto &it : buttons)
		{
			delete it;
			it = nullptr;
		}
	}
	
	if (!texts.empty())
	{
		for (auto &it : texts)
		{
			delete it;
			it = nullptr;
		}
	}
	
	if (!pressed.empty())
		pressed.clear();
	
	if (!states.empty())
		states.clear();

	if (!keys.empty())
		keys.clear();

	reset();
}

void EATools::reset()
{
	if (!pressed.empty())
	{
		for (auto it : pressed)
			it = false;
	}

	if (!states.empty())
	{
		for (auto it : states)
			it = 0;
	}

	hotKeyCounter = 0.0f;
	hotKeyState = 0.25f;
}

void EATools::resetButtons()
{
	for (auto &it : buttons)
		it->setActive(false);

	for (auto it : pressed)
		it = false;

	for (auto it : states)
		it = 0;
}



void EATools::load(const float& screen_w, const float& screen_h)
{
	free();

	this->screen_w = static_cast<int>(screen_w);
	this->screen_h = static_cast<int>(screen_h);

	for (int i = 0; i < COUNT; ++i)
	{
		buttons.push_back(new CircleButton);
		texts.push_back(new cmm::Text);
		pressed.push_back(false);
		states.push_back(0);

		Loading::add(texts[i]->setFont(cmm::JCANDLE_FONT_PATH));
		if (Loading::isError()) return;
		texts[i]->setSize(screen_w / 60);
		texts[i]->setAlpha(0xFF);
		texts[i]->setFillColor(cmm::LOADING_COLOR);
	}

	keys.push_back(sf::Keyboard::LControl);
	keys.push_back(sf::Keyboard::Space);
	keys.push_back(sf::Keyboard::LShift);
	
	buttons[DELETEKEY]->load("images/buttons/rubbish.png");
	buttons[HOTKEY]->load("images/buttons/hotkey.png");
	buttons[COLLISIONKEY]->load("images/buttons/wholecollision.png");
	if (Loading::isError()) return;
	
	for (auto &it : buttons)
	{
		it->setVolume(0.0f); // muted
		it->setScale(screen_w / 2560, screen_h / 1440);
	}
	
	buttons[DELETEKEY]->setPosition(screen_w - screen_w / 85 - buttons[DELETEKEY]->getWidth() * 3, screen_h / 144);
	buttons[HOTKEY]->setPosition(buttons[DELETEKEY]->getLeft() - screen_w / 256 - buttons[HOTKEY]->getWidth(), buttons[DELETEKEY]->getTop());
	buttons[COLLISIONKEY]->setPosition(buttons[HOTKEY]->getLeft() - screen_w / 256 - buttons[COLLISIONKEY]->getWidth(), buttons[DELETEKEY]->getTop());

	texts[DELETEKEY]->setText("Delete\nMode");
	texts[HOTKEY]->setText("Quick\nMode");
	texts[COLLISIONKEY]->setText("  Whole\nCollision");

	for (int i = 0; i < COUNT; ++i)
		texts[i]->setPosition(buttons[i]->getLeft() + buttons[i]->getWidth() / 2 - texts[i]->getWidth() / 2, buttons[i]->getBot() + screen_w / 300.0f);

	Loading::add(checkedIcon.load("images/icons/checkedicon.png"));
	if (Loading::isError()) return;
	checkedIcon.setScale(0.3, 0.3);
	checkedIcon.setAlpha(0xFF / 1.5);
}

bool EATools::handle(const sf::Event &event)
{
	for (int i = 0; i < COUNT; ++i)
	{
		buttons[i]->handle(event);
		if (buttons[i]->hasChanged())
		{
			if (states[i] != 2)				states[i] = 2;
			else if (states[i] == 2)		states[i] = pressed[i] ? 1 : 0;
			return true;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == keys[i])
			{
				pressed[i] = true;
				if (states[i] != 2)
					states[i] = 1;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == keys[i])
			{
				pressed[i] = false;
				if (states[i] != 2)
					states[i] = 0;

				if(i == HOTKEY)
					hotKeyCounter = 0.0f;
			}
		}
	}

	return false;
}

void EATools::drawTools(sf::RenderWindow* &window)
{
	for (int i = 0; i < COUNT; ++i)
	{
		if (states[i] != 0)
			buttons[i]->setActive(true);

		buttons[i]->draw(window);
		buttons[i]->setActive(false);
	}

	for (auto &it : texts)
		window->draw(*it);
}

void EATools::draw(sf::RenderWindow* &window, std::vector<cmm::Sprite*> &factory, const int& chosen)	// Draws thumbnails
{
	// Save current position.
	float tempX, tempY;
	tempX = factory[chosen]->getX();
	tempY = factory[chosen]->getY();

	// Draw
	int space = screen_h / 288;
	int startX = space * 3;
	int largestWidth = 0;
	float scaleX = factory[0]->getScaleX(), scaleY = factory[0]->getScaleY();

	for (unsigned i = 0; i < factory.size(); ++i)
	{
		if (i != chosen)	factory[i]->setAlpha(0xFF / 1.5);
		
		factory[i]->setScale(0.3, 0.3); // 30% of oryginal
		if (i != 0)
		{
			factory[i]->setPosition(startX, factory[i - 1]->getBot() + space);
			factory[i - 1]->setScale(scaleX, scaleY);
			scaleX = factory[i - 1]->getScaleX();
			scaleY = factory[i - 1]->getScaleY();
		}
		else
			factory[i]->setPosition(startX, screen_h / 6);

		if (factory[i]->getWidth() > largestWidth)
			largestWidth = static_cast<int>(factory[i]->getWidth());

		if (factory[i]->getBot() > screen_h / 8 * 7)
		{
			startX += largestWidth + space * 3;
			factory[i]->setPosition(startX, screen_h / 6);
			largestWidth = 0;
		}

		window->draw(*factory[i]);
		factory[i]->setAlpha(0xFF); // set back
	}

	factory[factory.size() - 1]->setScale(scaleX, scaleY); // set back 50% of oryginal for the first one

	// Set chosen icon
	scaleX = factory[chosen]->getScaleX();
	scaleY = factory[chosen]->getScaleY();
	factory[chosen]->setScale(0.3, 0.3);
	float x = factory[chosen]->getX() + factory[chosen]->getWidth() / 2 - checkedIcon.getWidth() / 2;
	float y = factory[chosen]->getY() + factory[chosen]->getHeight() / 2 - checkedIcon.getHeight() / 2;
	checkedIcon.setPosition(x, y);
	factory[chosen]->setScale(scaleX, scaleY);
	window->draw(checkedIcon);
	factory[chosen]->setPosition(tempX, tempY);	// Set back current position.
}

void EATools::mechanics(const float &elapsedTime)
{
	if (pressed[HOTKEY])
	{
		hotKeyCounter += elapsedTime;
	}

	ee::Collision::getCollision() = states[COLLISIONKEY] != 0 ? true : false;
}



bool EATools::isDeleteKeyPressed()
{
	return pressed[DELETEKEY];
}

bool EATools::isHotKeyPressed()
{
	return pressed[HOTKEY];
}

bool EATools::isCollisionKeyPressed()
{
	return pressed[COLLISIONKEY];
}

bool EATools::isHotKeyElapsed()
{
	if (hotKeyCounter > hotKeyState)
	{
		hotKeyCounter = 0.0f;
		return true;
	}
		
	return false;
}

bool EATools::isDeleteMode() const
{
	return states[DELETEKEY] != 0;
}
