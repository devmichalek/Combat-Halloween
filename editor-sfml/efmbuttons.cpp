#include "efmbuttons.h"

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

	if (!states.empty())
		states.clear();

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
	
	buttons[NEW]->load("images/icons/newfileicon.png");
	buttons[OPEN]->load("images/icons/openfileicon.png");
	buttons[SAVE]->load("images/icons/savefileicon.png");
	buttons[UPLOAD]->load("images/icons/uploadicon.png");
	buttons[COPY]->load("images/icons/copyicon.png");
	buttons[RENAME]->load("images/icons/renameicon.png");
	buttons[DELETE]->load("images/icons/erasericon.png");
	buttons[REFRESH]->load("images/icons/refreshicon.png");
	buttons[EXIT]->load("images/icons/exiticon.png");

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
	const char* pathToFont = "fonts/Jaapokki-Regular.otf";
	for (auto &it : labels)
	{
		it->setFont(pathToFont);
		it->setSize(screen_w / 120);
		it->setAlpha(0xFF);
		it->setFillColor(sf::Color::White);
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
	fileButton.setScale(screen_w / 2560, screen_h / 1440);
	fileButton.setPosition(screen_w - screen_w / 128 - fileButton.getWidth() * 2, screen_h / 144);

	fileButtonText.setFont(pathToFont);
	fileButtonText.setSize(screen_w / 60);
	fileButtonText.setAlpha(0xFF);
	fileButtonText.setFillColor(sf::Color::White);
	fileButtonText.setText("File");
	fileButtonText.setPosition(fileButton.getLeft() + fileButton.getWidth() / 2 - fileButtonText.getWidth() / 2, fileButton.getBot() + off);

	for (auto &it : buttons)
		it->setAlpha(0xFF / 1.5);
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
				it->setAlpha(0xFF / 1.5);

			float x = (float)event.mouseMove.x;
			float y = (float)event.mouseMove.y;

			for (auto &it : buttons)
				if (it->checkCollision(x, y))
					it->setAlpha(0xFF);
		}
	}
	else
	{
		fileButton.handle(event);
		active = fileButton.isActive();
		if (active)
		{
			for (auto &it : buttons)
				it->setAlpha(0xFF / 1.5);
		}
	}

	return false;
}

void EFMButtons::draw(sf::RenderWindow* &window)
{
	for (auto &it : labels)
		window->draw(it->get());

	for (auto &it : buttons)
		window->draw(it->get());
}

void EFMButtons::drawButton(sf::RenderWindow* &window)
{
	fileButton.draw(window);
	window->draw(fileButtonText.get());
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