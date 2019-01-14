#include "editoroptions.h"
#include "loading.h"
#include "colors.h"
#include "definitions.h"

EditorOptions::EditorOptions()
{
	free();
}

EditorOptions::~EditorOptions()
{
	free();
}

void EditorOptions::free()
{
	if (!keytextvec.empty())
	{
		for (auto &it : keytextvec)
		{
			delete it;
			it = nullptr;
		}

		keytextvec.clear();
	}

	if (!infotextvec.empty())
	{
		for (auto &it : infotextvec)
		{
			delete it;
			it = nullptr;
		}
		
		infotextvec.clear();
	}

	reset();
	lastPage = 3;
}

void EditorOptions::reset()
{
	currPage = 0;
	active = false;
}

void EditorOptions::load(const float& screen_w, const float& screen_h)
{
	free();

	float scale_x = screen_w / 1920;	if (scale_x > 1.0f)	scale_x = 1;
	float scale_y = screen_h / 1080;	if (scale_y > 1.0f)	scale_y = 1;

	// Set button.
	button.load("images/buttons/settings.png");
	if (Loading::isError())	return;
	button.setVolume(MIN_SOUND_VOLUME); // muted
	button.setScale(screen_w / 2560, screen_h / 1440);
	button.setPosition(screen_w - (screen_w / 256 + button.getWidth()) * 4, screen_h / 144);

	// Set button label.
	Loading::add(label.setFont(cmm::JCANDLE_FONT_PATH));
	if (Loading::isError())	return;
	label.setText("options");
	label.setAlpha(MAX_ALPHA);
	label.setPosition(button.getLeft() + button.getWidth() / 2 - label.getWidth() / 2.5, button.getBot() + screen_w / 300.0f);
	label.setSize(screen_w / 60);

	// Set board.
	Loading::add(plank.load("images/other/plank.png"));
	if (Loading::isError())	return;
	plank.setScale(scale_x, scale_y);
	plank.center(screen_w / 2, screen_h / 2);

	// Set black layer.
	blackLayer.setFillColor(sf::Color(0, 0, 0, 140));
	blackLayer.setSize(sf::Vector2f(screen_w, screen_h));
	blackLayer.setPosition(0, 0);

	// Set left/right buttons.
	Loading::add(leftbutton.load("images/icons/lefticon.png"));
	Loading::add(rightbutton.load("images/icons/righticon.png"));
	float factor = 0.9f;
	leftbutton.setScale(scale_x * factor, scale_y * factor);
	rightbutton.setScale(scale_x * factor, scale_y * factor);
	if (Loading::isError())	return;
	leftbutton.setPosition(plank.getLeft() + screen_w / 128, plank.getTop() + plank.getHeight() / 2 - leftbutton.getHeight() / 2);
	rightbutton.setPosition((plank.getRight() - screen_w / 128) - rightbutton.getWidth(), leftbutton.getY());
	leftbutton.setAlpha(MAX_ALPHA / 1.5);
	rightbutton.setAlpha(MAX_ALPHA / 1.5);

	// Set texts.
	for (int i = 0; i < LABELS::AMOUNT; ++i)
	{
		keytextvec.push_back(new cmm::Text);
		infotextvec.push_back(new cmm::Text);
		Loading::add(keytextvec.back()->setFont(cmm::JAPOKKI_FONT_PATH));
		Loading::add(infotextvec.back()->setFont(cmm::JAPOKKI_FONT_PATH));
		if (Loading::isError())	return;
		keytextvec.back()->setSize(plank.getWidth() / 25);
		infotextvec.back()->setSize(plank.getWidth() / 25);
		keytextvec.back()->setFillColor(cmm::DULL_IRON_COLOR);
		infotextvec.back()->setFillColor(cmm::WHITISH_COLOR);
		keytextvec.back()->setAlpha(MAX_ALPHA);
		infotextvec.back()->setAlpha(MAX_ALPHA);
	}

	keytextvec[ESCAPE]->setText("[ESC]");
	keytextvec[ENTER]->setText("[ENTER]");
	keytextvec[CTRL_Z]->setText("[CTRL+Z]");
	keytextvec[SPACE]->setText("[SPACE]");
	keytextvec[LCTRL]->setText("[LCTRL]");
	keytextvec[LSHIFT]->setText("[LSHIFT]");
	keytextvec[A]->setText("[A]\t\t");
	keytextvec[S]->setText("[S]\t\t");
	keytextvec[D]->setText("[D]\t\t");
	keytextvec[Z]->setText("[Z]\t\t");
	keytextvec[X]->setText("[X]\t\t");
	keytextvec[C]->setText("[C]\t\t");
	keytextvec[LEFT]->setText("[LEFT]");
	keytextvec[RIGHT]->setText("[RIGHT]");
	keytextvec[UP]->setText("[UP]");
	keytextvec[DOWN]->setText("[DOWN]");
	keytextvec[LEFTMOUSE]->setText("[LEFT MOUSE BUTTON]");
	keytextvec[RIGHTMOUSE]->setText("[RIGHT MOUSE BUTTON]");
	keytextvec[SCROLLMOUSE]->setText("[MOUSE SCROLL]");

	infotextvec[ESCAPE]->setText("Closes current open window. Turns off\ncurrent active mode.\nResets group and chosen entity from group.\n");
	infotextvec[ENTER]->setText("Agrees with current decision in message log.\nApproves choice yes/ok.\n");
	infotextvec[CTRL_Z]->setText("Undo. Back to previous world state.\nDetermines current state then goes back to\nthe previous.\n");
	infotextvec[SPACE]->setText("Temporary quick mode. Does actions like\nput (place) or remove. Based on current\nmode it deletes or puts entity very fast.\n");
	infotextvec[LCTRL]->setText("Temporary delete mode. Enables user to\nremove entity that mouse is pointing at.\n");
	infotextvec[LSHIFT]->setText("Temporary whole collision mode. This mode\nis very useful while placing tiles.\nTurnt on checks the whole rect occupied by\nentity.\n\n");
	infotextvec[A]->setText("Moves to the previous group of entities.");
	infotextvec[S]->setText("Reset the chosen group to none.");
	infotextvec[D]->setText("Moves to the succeding group of entities.\n");
	infotextvec[Z]->setText("Goes to previous entity from the group.");
	infotextvec[X]->setText("Goes to nearest middle one from the group.");
	infotextvec[C]->setText("Goes to next entity from the group.\n");
	infotextvec[LEFT]->setText("Moves current world content's position\nleftward (it does not change entities position).\n");
	infotextvec[RIGHT]->setText("Moves current world content's position\nrightward (same as above).\n");
	infotextvec[UP]->setText("Moves current world content's position upward\n(same as above).\n");
	infotextvec[DOWN]->setText("Moves current world content's position\ndownward (same as above).\n");
	infotextvec[LEFTMOUSE]->setText("Puts entity or removes\n(depends on current mode).\n\n");
	infotextvec[RIGHTMOUSE]->setText("If mouse cursor is hovered\nabove the entity it opens\nthe options of a group.\n\n\n");
	infotextvec[SCROLLMOUSE]->setText("Changes entity of chosen group\nto upward or downward one.");

	// Set page text.
	Loading::add(pageText.setFont(cmm::JCANDLE_FONT_PATH));
	if (Loading::isError())	return;
	pageText.setAlpha(MAX_ALPHA);
	pageText.setSize(plank.getWidth() / 20);
	setPageText();
}

void EditorOptions::handle(const sf::Event &event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			float x = (float)event.mouseButton.x;
			float y = (float)event.mouseButton.y;

			if (!active && button.handle(event))
			{
				active = button.isActive();
				if (active)
					setText();
				return;
			}

			if (leftbutton.checkCollision(x, y))
			{
				if (isAbleToGoLeft())
				{
					--currPage;
					setText();
				}
			}
			else if (rightbutton.checkCollision(x, y))
			{
				if (isAbleToGoRight())
				{
					++currPage;
					setText();
				}
			}
			else if (!plank.checkCollision(x, y))
			{
				active = false;
				button.setActive(false);
				reset();
			}
		}
	}

	if (!active)
		return;

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			active = false;
			button.setActive(false);
			reset();
			return;
		}
	}

	// hovering...
	if (event.type == sf::Event::MouseMoved)
	{
		leftbutton.setAlpha(MAX_ALPHA / 1.5);
		rightbutton.setAlpha(MAX_ALPHA / 1.5);

		float x = (float)event.mouseMove.x;
		float y = (float)event.mouseMove.y;

		if (isAbleToGoLeft() && leftbutton.checkCollision(x, y))
			leftbutton.setAlpha(MAX_ALPHA);
		else if (isAbleToGoRight() &&rightbutton.checkCollision(x, y))
			rightbutton.setAlpha(MAX_ALPHA);
	}
}

void EditorOptions::drawButton(sf::RenderWindow* &window)
{
	// Draw button and label always.
	button.draw(window);
	window->draw(label);
}

void EditorOptions::draw(sf::RenderWindow* &window)
{
	if (!active)
		return;

	window->draw(blackLayer);
	window->draw(plank);

	// Draw descriptions / texts.
	for (int i = first; i <= last; ++i)
	{
		window->draw(*keytextvec[i]);
		window->draw(*infotextvec[i]);
	}

	// Draw left/right buttons.
	if (currPage != 0)
		window->draw(leftbutton);
	if (currPage != lastPage)
		window->draw(rightbutton);
	window->draw(pageText);
}

void EditorOptions::setText()
{
	setPageText();
	setBorders();

	// set position of current scope
	keytextvec[first]->setPosition(plank.getX() + plank.getWidth() / 64, plank.getY() + plank.getHeight() / 64);
	infotextvec[first]->setPosition(keytextvec[first]->getX() + keytextvec[first]->getWidth() + plank.getWidth() / 64, keytextvec[first]->getY());
	for (int i = first + 1; i <= last; ++i)
	{
		keytextvec[i]->setPosition(keytextvec[first]->getX(), infotextvec[i - 1]->getBot());
		infotextvec[i]->setPosition(keytextvec[i]->getX() + keytextvec[i]->getWidth() + plank.getWidth() / 64, infotextvec[i - 1]->getBot());
	}
}

void EditorOptions::setPageText()
{
	pageText.setText(std::to_string(currPage) + "/" + std::to_string(lastPage));
	pageText.setPosition(plank.getLeft() + plank.getWidth() - pageText.getWidth() * 1.2, plank.getTop() + plank.getHeight() - plank.getWidth() / 15);
}

void EditorOptions::setBorders()
{
	if (currPage == 0)
	{
		first = 0;
		last = SPACE;
	}
	else if (currPage == 1)
	{
		first = LCTRL;
		last = C;
	}
	else if (currPage == lastPage - 1)
	{
		first = LEFT;
		last = DOWN;
	}
	else
	{
		first = LEFTMOUSE;
		last = SCROLLMOUSE;
	}
}

bool EditorOptions::isAbleToGoLeft()
{
	return currPage > 0;
}

bool EditorOptions::isAbleToGoRight()
{
	return currPage < lastPage;
}