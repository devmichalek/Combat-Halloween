#include "efmbuttons.h"
#include "loading.h"
#include "definitions.h"

EFMButtons::EFMButtons()
{
	free();
}

EFMButtons::~EFMButtons()
{
	free();
}

void EFMButtons::free()
{
	reset();

	if (!states.empty())
		states.clear();

	if (!labels.empty())
	{
		for (auto &it : labels)
		{
			delete it;
			it = nullptr;
		}

		labels.clear();
	}

	if (!buttons.empty())
	{
		for (auto &it : buttons)
		{
			delete it;
			it = nullptr;
		}

		buttons.clear();
	}
}

void EFMButtons::reset()
{
	active = false;

	for (auto it : states)
		it = false;

	fileButton.setActive(false);
}



void EFMButtons::load(const float &screen_w, const float &screen_h, const float l, const float &r, const float &y)
{
	free();

	float scale_x = screen_w / 1920;	if (scale_x > 1.0f)	scale_x = 1;
	float scale_y = screen_h / 1080;	if (scale_y > 1.0f)	scale_y = 1;

	for (int i = 0; i < SIZE; ++i)
	{
		states.push_back(false);
		if (i < EXIT)
			labels.push_back(new cmm::Text);
		buttons.push_back(new cmm::Sprite);
	}

	// Buttons
	
	Loading::add(buttons[NEW]->load("images/icons/newfileicon.png"));
	Loading::add(buttons[OPEN]->load("images/icons/openfileicon.png"));
	Loading::add(buttons[SAVE]->load("images/icons/savefileicon.png"));
	Loading::add(buttons[UPLOAD]->load("images/icons/uploadicon.png"));
	Loading::add(buttons[COPY]->load("images/icons/copyicon.png"));
	Loading::add(buttons[RENAME]->load("images/icons/renameicon.png"));
	Loading::add(buttons[DELETE]->load("images/icons/erasericon.png"));
	Loading::add(buttons[REFRESH]->load("images/icons/refreshicon.png"));
	Loading::add(buttons[EXIT]->load("images/icons/exiticon.png"));
	if (Loading::isError())	return;

	float factor = 0.9f;
	for (auto &it : buttons)
		it->setScale(scale_x * factor, scale_y * factor);

	float off = screen_w / 150.0f;
	buttons[NEW]->setPosition(l + off, y + off);
	buttons[OPEN]->setPosition(buttons[NEW]->getRight() + off / 2, buttons[NEW]->getTop());
	buttons[SAVE]->setPosition(buttons[OPEN]->getRight() + off, buttons[NEW]->getTop());
	buttons[UPLOAD]->setPosition(buttons[SAVE]->getRight() + off, buttons[NEW]->getTop());
	buttons[COPY]->setPosition(buttons[UPLOAD]->getRight() + off, buttons[NEW]->getTop());
	buttons[RENAME]->setPosition(buttons[COPY]->getRight() + off, buttons[NEW]->getTop());
	buttons[DELETE]->setPosition(buttons[RENAME]->getRight() + off, buttons[NEW]->getTop());
	buttons[REFRESH]->setPosition(buttons[DELETE]->getRight() + off, buttons[NEW]->getTop());
	buttons[EXIT]->setPosition(r - buttons[EXIT]->getWidth() - off, buttons[NEW]->getTop());



	// Labels
	const char* pathToFont = cmm::JAPOKKI_FONT_PATH;
	for (auto &it : labels)
	{
		Loading::add(it->setFont(pathToFont));
		if (Loading::isError())	return;
		it->setSize(screen_w / 120);
		it->setAlpha(MAX_ALPHA);
		it->setFillColor(cmm::LOADING_COLOR);
	}

	labels[NEW]->setText("New");
	labels[OPEN]->setText("Open");
	labels[SAVE]->setText("Save");
	labels[UPLOAD]->setText("Upload");
	labels[COPY]->setText("Copy");
	labels[RENAME]->setText("Rename");
	labels[DELETE]->setText("Delete");
	labels[REFRESH]->setText("Refresh");

	for (unsigned i = 0; i < labels.size(); ++i)
		labels[i]->setPosition(buttons[i]->getX() + buttons[i]->getWidth() / 2 - labels[i]->getWidth() / 2, buttons[i]->getBot() + off);



	// The Rest
	fileButton.load("images/buttons/save.png");
	if (Loading::isError())	return;
	fileButton.setVolume(MIN_SOUND_VOLUME); // muted
	fileButton.setScale(screen_w / 2560, screen_h / 1440);
	fileButton.setPosition(screen_w - screen_w / 128 - fileButton.getWidth() * 2, screen_h / 144);

	Loading::add(fileButtonText.setFont(cmm::JCANDLE_FONT_PATH));
	if (Loading::isError())	return;
	fileButtonText.setSize(screen_w / 60);
	fileButtonText.setAlpha(MAX_ALPHA);
	fileButtonText.setFillColor(cmm::LOADING_COLOR);
	fileButtonText.setText("File");
	fileButtonText.setPosition(fileButton.getLeft() + fileButton.getWidth() / 2 - fileButtonText.getWidth() / 2, fileButton.getBot() + off / 2);

	for (auto &it : buttons)
		it->setAlpha(MAX_ALPHA / 1.5);
}

bool EFMButtons::handle(const sf::Event &event)
{
	if (active)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				float x = (float)event.mouseButton.x;
				float y = (float)event.mouseButton.y;

				if (buttons[EXIT]->checkCollision(x, y))
				{
					active = false;
					states[EXIT] = true;
					fileButton.setActive(false);
					return true;
				}
				else
				{
					for (unsigned i = 0; i < EXIT; ++i)
					{
						if (buttons[i]->checkCollision(x, y))
						{
							states[i] = true;
							return true;
						}
					}
				}
			}
		}

		// hovering...
		if (event.type == sf::Event::MouseMoved)
		{
			for (auto &it : buttons)
				it->setAlpha(MAX_ALPHA / 1.5);

			float x = (float)event.mouseMove.x;
			float y = (float)event.mouseMove.y;

			for (auto &it : buttons)
				if (it->checkCollision(x, y))
					it->setAlpha(MAX_ALPHA);
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				active = false;
				fileButton.setActive(false);
				return false;
			}
		}
	}
	else
	{
		fileButton.handle(event);
		active = fileButton.isActive();
		if (active)
		{
			for (auto &it : buttons)
				it->setAlpha(MAX_ALPHA / 1.5);
		}
	}

	return false;
}

void EFMButtons::draw(sf::RenderWindow* &window)
{
	for (auto &it : labels)
		window->draw(*it);

	for (auto &it : buttons)
		window->draw(*it);
}

void EFMButtons::drawButton(sf::RenderWindow* &window)
{
	fileButton.draw(window);
	window->draw(fileButtonText);
}

void EFMButtons::mechanics(/*const double &elapsedTime*/)
{
	if (fileButton.isActive())
	{
		active = true;
	}
}




bool EFMButtons::isNewFile()
{
	if (states[NEW])
	{
		states[NEW] = false;
		return true;
	}

	return false;
}

bool EFMButtons::isOpenFile()
{
	if (states[OPEN])
	{
		states[OPEN] = false;
		return true;
	}

	return false;
}

bool EFMButtons::isSaveFile()
{
	if (states[SAVE])
	{
		states[SAVE] = false;
		return true;
	}

	return false;
}

bool EFMButtons::isUploadFile()
{
	if (states[UPLOAD])
	{
		states[UPLOAD] = false;
		return true;
	}

	return false;
}

bool EFMButtons::isCopyFile()
{
	if (states[COPY])
	{
		states[COPY] = false;
		return true;
	}

	return false;
}

bool EFMButtons::isRenameFile()
{
	if (states[RENAME])
	{
		states[RENAME] = false;
		return true;
	}

	return false;
}

bool EFMButtons::isDeleteFile()
{
	if (states[DELETE])
	{
		states[DELETE] = false;
		return true;
	}

	return false;
}

bool EFMButtons::isRefresh()
{
	if (states[REFRESH])
	{
		states[REFRESH] = false;
		return true;
	}

	return false;
}

bool EFMButtons::isExit()
{
	if (states[EXIT])
	{
		states[EXIT] = false;
		return true;
	}

	return false;
}

const bool& EFMButtons::isActive() const
{
	return active;
}

void EFMButtons::setActive()
{
	active = true;
	fileButton.setActive(true);
}


float EFMButtons::getBot() const
{
	return labels[0]->getBot();
}