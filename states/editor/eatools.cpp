#include "eatools.h"
#include "loading.h"
#include "definitions.h"
#include "eeentity.h"

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
	for (auto &it : buttons)
		it->setActive(false);

	for (auto it : pressed)
		it = false;

	for (auto it : states)
		it = 0;

	type = VOID;
	chosen = 0;

	ctrl_key = false;
	z_key = false;
	undoKeyCounter = 0.0f;
	undoKeyState = 0.1f;

	change = false;
	redBack = false;

	hotKeyCounter = 0.0f;
	hotKeyState = 0.25f;
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
		texts[i]->setAlpha(MAX_ALPHA);
		texts[i]->setFillColor(cmm::LOADING_COLOR);
	}

	keys.push_back(sf::Keyboard::LControl);
	keys.push_back(sf::Keyboard::Space);
	keys.push_back(sf::Keyboard::LShift);
	
	buttons[DELETEKEY]->load("images/buttons/rubbish.png");
	buttons[HOTKEY]->load("images/buttons/hotkey.png");
	buttons[WHOLECOLLISIONKEY]->load("images/buttons/wholecollision.png");
	if (Loading::isError()) return;
	
	for (auto &it : buttons)
	{
		it->setVolume(MIN_SOUND_VOLUME); // muted
		it->setScale(screen_w / 2560, screen_h / 1440);
	}
	
	buttons[DELETEKEY]->setPosition(screen_w - screen_w / 85 - buttons[DELETEKEY]->getWidth() * 3, screen_h / 144);
	buttons[HOTKEY]->setPosition(buttons[DELETEKEY]->getLeft() - screen_w / 256 - buttons[HOTKEY]->getWidth(), buttons[DELETEKEY]->getTop());
	buttons[WHOLECOLLISIONKEY]->setPosition(buttons[HOTKEY]->getLeft() - screen_w / 256 - buttons[WHOLECOLLISIONKEY]->getWidth(), buttons[DELETEKEY]->getTop());

	texts[DELETEKEY]->setText("Delete\nMode");
	texts[HOTKEY]->setText("Quick\nMode");
	texts[WHOLECOLLISIONKEY]->setText("  Whole\nCollision");

	for (int i = 0; i < COUNT; ++i)
		texts[i]->setPosition(buttons[i]->getLeft() + buttons[i]->getWidth() / 2 - texts[i]->getWidth() / 2, buttons[i]->getBot() + screen_w / 300.0f);

	shape.setFillColor(cmm::DULL_IRON_COLOR);
	Loading::add(checkedIcon.load("images/icons/checkedicon.png"));
	if (Loading::isError()) return;
	checkedIcon.setScale(0.3, 0.3);
	checkedIcon.setAlpha(MAX_ALPHA / 1.5);
}

void EATools::handle(const sf::Event &event, const int &amount)
{
	for (int i = 0; i < COUNT; ++i)
	{
		buttons[i]->handle(event);
		if (buttons[i]->hasChanged())
		{
			if (states[i] != 2)				states[i] = 2;
			else if (states[i] == 2)		states[i] = pressed[i] ? 1 : 0;
			type = cmm::Kind::VOID;
			chosen = 0;
			return;
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

	// scroll - changing chosen
	if (type != VOID)
	{
		if (event.type == sf::Event::MouseWheelMoved)
		{
			if (event.mouseWheel.delta < 0)
			{
				(chosen < amount - 1) ? (++chosen) : (chosen = 0);
				change = true;
			}
			else
			{
				(chosen > 0) ? (--chosen) : (chosen = amount - 1);
				change = true;
			}
		}
	}

	// Changing type and chosen.
	if (event.type == sf::Event::KeyPressed)
	{
		change = true;
		int code = event.key.code;

		if (isDeleteKeyPressed())
		{
			type = VOID;
			chosen = 0;
		}
		else if (code == sf::Keyboard::Escape)
		{
			reset();
			change = true;
		}
		else if (!isDeleteMode())
		{
			int old_type = type;
			switch(code)
			{ 
				case sf::Keyboard::Z:	(chosen > 0)			? (--chosen)	: (chosen = amount - 1);break;
				case sf::Keyboard::X:	(chosen == 0)			? (chosen = 0)	: (chosen /= 2);		break;
				case sf::Keyboard::C:	(chosen < amount - 1)	? (++chosen)	: (chosen = 0);			break;
				case sf::Keyboard::A:	(type > VOID)			? (--type)		: (type = AMOUNT);		break;
				case sf::Keyboard::S:	(type = VOID);													break;
				case sf::Keyboard::D:	(type < AMOUNT)			? (++type)		: (type = VOID + 1);	break;
				default:				(change = false);												break;
			}

			if (old_type != type) // If type has changed reset chosen.
				chosen = 0;
		}
	}

	// Undo Ctrl + Z
	if (event.type == sf::Event::KeyPressed)
	{
		int code = event.key.code;
		if (code == sf::Keyboard::LControl)
			ctrl_key = true;

		if (!z_key && ctrl_key)
		{
			if (code == sf::Keyboard::Z)
				z_key = true;
		}
	}

	if (event.type == sf::Event::KeyReleased)
	{
		int code = event.key.code;
		if (code == sf::Keyboard::LControl)	ctrl_key = false;
		if (code == sf::Keyboard::Z)		z_key = false;
	}
}

void EATools::draw(sf::RenderWindow* &window)
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

void EATools::thumbnail(sf::RenderWindow* &window, std::vector<cmm::Sprite*> &sprites, const int& chosen)
{
	// Save current position.
	float tempX, tempY;
	tempX = sprites[chosen]->getX();
	tempY = sprites[chosen]->getY();

	// Draw
	int space = screen_h / 288;
	int startX = space * 3;
	int largestWidth = 0;
	float scaleX = sprites[0]->getScaleX(), scaleY = sprites[0]->getScaleY();

	for (unsigned i = 0; i < sprites.size(); ++i)
	{
		sprites[i]->setScale(0.3, 0.3); // 30% of oryginal
		if (i != 0)
		{
			sprites[i]->setPosition(startX, sprites[i - 1]->getBot() + space);
			sprites[i - 1]->setScale(scaleX, scaleY);
			scaleX = sprites[i - 1]->getScaleX();
			scaleY = sprites[i - 1]->getScaleY();
		}
		else
			sprites[i]->setPosition(startX, screen_h / 6);

		if (sprites[i]->getWidth() > largestWidth)
			largestWidth = static_cast<int>(sprites[i]->getWidth());

		if (sprites[i]->getBot() > screen_h / 8 * 7)
		{
			startX += largestWidth + space * 3;
			sprites[i]->setPosition(startX, screen_h / 6);
			largestWidth = 0;
		}

		if (i == chosen)
		{
			shape.setSize(sf::Vector2f(sprites[i]->getWidth() * 1.05f, sprites[i]->getHeight() * 1.05f));
			shape.setPosition(sf::Vector2f(sprites[i]->getX() - sprites[i]->getWidth() * 0.025f, sprites[i]->getY() - sprites[i]->getHeight() * 0.025f));
			window->draw(shape);
		}

		window->draw(*sprites[i]);
	}

	sprites[sprites.size() - 1]->setScale(scaleX, scaleY); // set back 50% of oryginal for the first one

														   // Set chosen icon
	scaleX = sprites[chosen]->getScaleX();
	scaleY = sprites[chosen]->getScaleY();
	sprites[chosen]->setScale(0.3, 0.3);
	float x = sprites[chosen]->getX() + sprites[chosen]->getWidth() / 2 - checkedIcon.getWidth() / 2;
	float y = sprites[chosen]->getY() + sprites[chosen]->getHeight() / 2 - checkedIcon.getHeight() / 2;
	checkedIcon.setPosition(x, y);
	sprites[chosen]->setScale(scaleX, scaleY);
	window->draw(checkedIcon);
	sprites[chosen]->setPosition(tempX, tempY);	// Set back current position.
}

void EATools::mechanics(const float &elapsedTime)
{
	if (pressed[HOTKEY] || (states[HOTKEY] && pressed[DELETEKEY]))
	{
		hotKeyCounter += elapsedTime;
	}

	if (z_key && ctrl_key)
	{
		undoKeyCounter += elapsedTime;
	}

	ee::Entity::getWholeCollision() = states[WHOLECOLLISIONKEY] != 0 ? true : false;
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

bool EATools::isUndoKeyElapsed()
{
	if (undoKeyCounter > undoKeyState)
	{
		undoKeyCounter = 0.0f;
		return true;
	}

	return false;
}

bool EATools::isChange()
{
	if (change)
	{
		change = false;
		return true;
	}

	return false;
}