#include "efmlibrary.h"
#include "loading.h"

EFMLibrary::EFMLibrary()
{
	free();
}

EFMLibrary::~EFMLibrary()
{
	free();
}

void EFMLibrary::free()
{
	page = 0;
	gridSquare = 9;
	chosen = -1;
	ableToGoLeft = false;
	ableToGoRight = false;
	
	if (!icons.empty())
	{
		for (auto &it : icons)
		{
			delete it;
			it = nullptr;
		}

		icons.clear();
	}

	if (!strLabels.empty())
		strLabels.clear();

	if (!textLabels.empty())
	{
		for (auto &it : textLabels)
		{
			delete it;
			it = nullptr;
		}

		textLabels.clear();
	}

	if (!iconPos.empty())
		iconPos.clear();
}

void EFMLibrary::reset()
{
	page = 0;
	chosen = -1;
	setPageText();
}



void EFMLibrary::load(const float &screen_w, const float &screen_h, sf::FloatRect newPlank)
{
	free();

	float scale_x = screen_w / 1920;	if (scale_x > 1.0f)	scale_x = 1;
	float scale_y = screen_h / 1080;	if (scale_y > 1.0f)	scale_y = 1;

	this->plank = newPlank;

	// Icons
	for (int i = 0; i < SIZE; ++i)
		icons.push_back(new cmm::Sprite);

	Loading::add(icons[LEFT]->load("images/icons/lefticon.png"));
	Loading::add(icons[RIGHT]->load("images/icons/righticon.png"));
	Loading::add(icons[WORLD]->load("images/icons/fileicon.png"));
	Loading::add(icons[CHECKED]->load("images/icons/checkedicon.png"));
	if (Loading::isError())	return;

	float factor = 0.9f;
	float off = screen_w / 200.0f;
	for(auto &it : icons)
		it->setScale(scale_x * factor, scale_y * factor);

	icons[LEFT]->setPosition(plank.left + off, plank.top + plank.height / 2 - icons[LEFT]->getHeight() / 2);
	icons[RIGHT]->setPosition(plank.left + plank.width - off - icons[RIGHT]->getWidth(), icons[LEFT]->getTop());
	icons[LEFT]->setAlpha(0xFF / 1.5);
	icons[RIGHT]->setAlpha(0xFF / 1.5);

	// The Rest
	Loading::add(pageText.setFont(cmm::JAPOKKI_FONT_PATH));
	if (Loading::isError())	return;
	pageText.setSize(plank.width / 20);
	pageText.setAlpha(0xFF);
	setPageText();
}

bool EFMLibrary::handle(const sf::Event &event, const bool &status)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			float x = (float)event.mouseButton.x;
			float y = (float)event.mouseButton.y;

			if (icons[LEFT]->checkCollision(x, y))
			{
				if (ableToGoLeft)
				{
					--page;
					setPageText();
				}
			}
			else if (icons[RIGHT]->checkCollision(x, y))
			{
				if (ableToGoRight)
				{
					++page;
					setPageText();
				}
			}
			else if(!status)	// maybe icon?
			{
				chosen = -1;

				int start, end;
				getPositions(start, end);
				for (int i = start; i < end; ++i)
				{
					icons[WORLD]->setPosition(iconPos[i].x, iconPos[i].y);
					if (icons[WORLD]->checkCollision(x, y))
					{
						icons[CHECKED]->setPosition(icons[WORLD]->getX(), icons[WORLD]->getY());
						chosen = i;
						break;
					}
				}

				return true;
			}
		}
	}

	// hovering...
	if (event.type == sf::Event::MouseMoved)
	{
		icons[LEFT]->setAlpha(0xFF / 1.5);
		icons[RIGHT]->setAlpha(0xFF / 1.5);

		float x = (float)event.mouseMove.x;
		float y = (float)event.mouseMove.y;

		if (icons[LEFT]->checkCollision(x, y) && ableToGoLeft)
			icons[LEFT]->setAlpha(0xFF);
		else if (icons[RIGHT]->checkCollision(x, y) && ableToGoRight)
			icons[RIGHT]->setAlpha(0xFF);
	}

	return false;
}

void EFMLibrary::draw(sf::RenderWindow* &window)
{
	if (ableToGoLeft)	window->draw(*icons[LEFT]);
	if (ableToGoRight)	window->draw(*icons[RIGHT]);

	int start, end;
	getPositions(start, end);
	for (int i = start; i < end; ++i)
	{
		icons[WORLD]->setPosition(iconPos[i].x, iconPos[i].y);
		window->draw(*icons[WORLD]);
		window->draw(*textLabels[i]);
	}

	window->draw(pageText);

	if (chosen >= start && chosen < end)
	{
		window->draw(*icons[CHECKED]);
	}
}

void EFMLibrary::mechanics(const double &elapsedTime)
{

}




void EFMLibrary::refresh(std::vector<std::string> copy)
{
	page = 0;
	chosen = -1;

	// Erase other files.
	for (std::vector<std::string>::iterator it = copy.begin(); it != copy.end();)
	{
		int size = it->size() - 1;

		std::string str = *it;
		if (size - 3 < 1)
			it = copy.erase(it);
		else if (str[size] != 'w' || str[size - 1] != 'h' || str[size - 2] != 'c' || str[size - 3] != '.')
			it = copy.erase(it);
		else
			++it;
	}

	// Clear world names.
	if (!strLabels.empty())
		strLabels.clear();

	// Clear world texts.
	if (!textLabels.empty())
	{
		for (auto &it : textLabels)
		{
			delete it;
			it = nullptr;
		}

		textLabels.clear();
	}

	// Clear icon positions
	if (!iconPos.empty())
		iconPos.clear();

	const char* pathToFont = cmm::JAPOKKI_FONT_PATH;
	for (auto &it : copy)
	{
		textLabels.push_back(new cmm::Text);
		int n = textLabels.size() - 1;
		textLabels[n]->setFont(pathToFont);
		textLabels[n]->setSize(plank.width / 30);
		strLabels.push_back(it);

		std::string outStr = it.substr(0, it.size() - 4);
		if (it.size() > 21)			outStr = it.substr(0, 11) + "\n" + it.substr(12, 8) + "...";
		else if (it.size() > 12)	outStr = it.substr(0, 8) + "..."; // 11 c
		textLabels[n]->setText(outStr);

		textLabels[n]->setAlpha(0xFF);
	}

	// Positioning.
	int xc = 0, yc = 0;
	int gridLength = (int)sqrt(gridSquare) - 1;
	float off = plank.width / 30;
	float w = plank.width / 5;
	int startX = (int)(plank.left + plank.width / 2 - (w * (gridLength + 1) + off * gridLength) / 2 + off);
	for (unsigned i = 0; i < textLabels.size(); ++i)
	{
		iconPos.push_back(sf::Vector2f());
		iconPos[i].x = startX + off + (w + off) * xc;
		iconPos[i].y = static_cast<float>((plank.top + plank.height / 4.5) + off * 2 + w * yc);

		textLabels[i]->setPosition(iconPos[i].x + icons[WORLD]->getWidth() / 2 - textLabels[i]->getWidth() / 2, iconPos[i].y + icons[WORLD]->getHeight());

		++xc;

		if (xc > gridLength)
		{
			xc = 0;
			++yc;
		}

		if (yc > gridLength)	yc = 0;
	}

	textLabels.shrink_to_fit();
	iconPos.shrink_to_fit();
	setPageText();
}

bool EFMLibrary::isChosen()
{
	return chosen != -1;
}

const std::string& EFMLibrary::getChosenStr() const
{
	return strLabels[chosen];
}

void EFMLibrary::setPageText()
{
	pageText.setText(std::to_string(page) + "/" + std::to_string(iconPos.size() / gridSquare));
	pageText.setPosition(plank.left + plank.width - pageText.getWidth() * 1.2, plank.top + plank.height - plank.width / 15);

	ableToGoLeft = page == 0 ? false : true;

	if((float)page + 1 < (float)iconPos.size() / gridSquare)
		ableToGoRight = true;
	else
		ableToGoRight = false;
}

void EFMLibrary::getPositions(int &s, int &e)
{
	s = page == 0 ? 0 : gridSquare * page;
	int iconPage = gridSquare + gridSquare * page;
	e = (int)iconPos.size() > iconPage ? iconPage : iconPos.size();
}