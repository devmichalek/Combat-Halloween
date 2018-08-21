#include "eagrid.h"
#include "state.h"

EAGrid::EAGrid()
{
	free();
}

EAGrid::~EAGrid()
{
	free();
}

void EAGrid::free()
{
	reset();
	width = 0;

	if (!texts.empty())
	{
		for (auto &it : texts)
		{
			delete it;
			it = nullptr;
		}

		texts.clear();
	}
}

void EAGrid::reset()
{
	grid = false;
	mouseX = mouseY = -1;
}



void EAGrid::load(const float &screen_w, const float &screen_h, const int &width)
{
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	this->width = width;
	sf::Color color = User::getLockedColor();
	color.a = 0xFF / 3;
	lineX.setSize(sf::Vector2f(1, screen_h));
	lineX.setPosition(0, 0);
	lineX.setFillColor(color);
	lineY.setSize(sf::Vector2f(screen_w, 1));
	lineY.setPosition(0, 0);
	lineY.setFillColor(color);

	suppX.setSize(sf::Vector2f(1, width / 2));
	suppY.setSize(sf::Vector2f(width / 2, 1));
	suppX.setFillColor(color);
	suppY.setFillColor(color);

	const char* pathToFont = "fonts/jcandlestickextracond.ttf";
	xyText.setFont(pathToFont);
	xyText.setSize(screen_w / 80);
	xyText.setAlpha(0xFF / 3);
	xyText.setFillColor(User::getLockedColor());

	for (int i = 0; i < TEXTS::SIZE; ++i)
	{
		texts.push_back(new cmm::Text);
		texts[i]->setFont(pathToFont);
		texts[i]->setSize(screen_w / 60);
		texts[i]->setAlpha(0xFF);
		i % 2 == 0 ? texts[i]->setFillColor(User::getLockedColor()) : texts[i]->setFillColor(User::getLoadingColor());
	}

	texts[GRIDFORM]->setText("Grid:");
	texts[CHOSENFORM]->setText("Chosen:");
	texts[CATEGORYFORM]->setText("Category:");
	texts[GRIDFORM]->setPosition(screen_w / 8, screen_h / 144);
	texts[CHOSENFORM]->setPosition(texts[GRIDFORM]->getX(), texts[GRIDFORM]->getBot() + screen_h / 144);
	texts[CATEGORYFORM]->setPosition(texts[GRIDFORM]->getX(), texts[CHOSENFORM]->getBot() + screen_h / 144);
}

void EAGrid::handle(const sf::Event& event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		mouseX = (float)event.mouseMove.x;
		mouseY = (float)event.mouseMove.y;

		// Calculate grid
		if (grid)
		{
			gridX = mouseX;
			gridY = mouseY;
			int halfWidth = width / 2;

			int count = 0;
			while (gridX >= halfWidth)
			{
				gridX -= halfWidth;
				count++;
			}
			gridX = count * halfWidth;

			count = 0;
			int diff = static_cast <int> (screen_h) % static_cast <int> (halfWidth);
			while (gridY - diff >= halfWidth)
			{
				gridY -= halfWidth;
				count++;
			}
			gridY = count * halfWidth + diff;
		}

		// Set text.
		int rX = static_cast<int>(grid ? gridX : mouseX);
		int rY = static_cast<int>(grid ? gridY : mouseY);
		std::string result = "x: " + std::to_string(rX);
		result += " y: " + std::to_string(rY);
		xyText.setText(result);
	}
}

void EAGrid::draw(sf::RenderWindow* &window)
{
	if (!grid)
	{
		lineX.setPosition(mouseX, 0);
		lineY.setPosition(0, mouseY);

		window->draw(lineX);
		window->draw(lineY);

		xyText.setPosition(mouseX + width / 16, mouseY - width / 8 - xyText.getHeight());
	}
	else
	{
		lineX.setPosition(gridX, 0);
		lineY.setPosition(0, gridY);
		window->draw(lineX);
		window->draw(lineY);

		lineX.setPosition(gridX + width, 0);
		lineY.setPosition(0, gridY + width);
		window->draw(lineX);
		window->draw(lineY);

		suppX.setPosition(gridX + width / 2, gridY - width / 4);
		suppY.setPosition(gridX - width / 4, gridY + width / 2);
		window->draw(suppX);
		window->draw(suppY);

		xyText.setPosition(gridX + width + 1, gridY - 1);
	}

	window->draw(xyText.get());

	for (auto & it : texts)
	{
		window->draw(it->get());
	}
}



float EAGrid::getX() const
{
	return grid ? gridX : mouseX;
}

float EAGrid::getY() const
{
	return grid ? gridY : mouseY;
}

void EAGrid::turnOn()
{
	grid = true;
}

void EAGrid::turnOff()
{
	grid = false;
}

const bool& EAGrid::isActive() const
{
	return grid;
}

void EAGrid::setGridStr()
{
	grid ? texts[GRID]->setText("On") : texts[GRID]->setText("Off");
	grid ? texts[GRID]->setFillColor(User::getGreenColor()) : texts[GRID]->setFillColor(User::getErrorColor());
	texts[GRID]->setPosition(texts[CATEGORYFORM]->getRight() + width / 4, texts[GRIDFORM]->getY());
}

void EAGrid::setChosenStr(std::string line)
{
	texts[CHOSEN]->setText(line);
	texts[CHOSEN]->setPosition(texts[CATEGORYFORM]->getRight() + width / 4, texts[CHOSENFORM]->getY());
}

void EAGrid::setCategoryStr(std::string line)
{
	texts[CATEGORY]->setText(line);
	texts[CATEGORY]->setPosition(texts[CATEGORYFORM]->getRight() + width / 4, texts[CATEGORYFORM]->getY());
}