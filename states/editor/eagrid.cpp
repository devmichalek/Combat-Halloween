#include "eagrid.h"
#include "logconsole.h"
#include "loading.h"

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

	if (!arrows.empty())
	{
		for (auto &it : arrows)
		{
			delete it;
			it = nullptr;
		}

		arrows.clear();
	}

	width = 0;
	offsetX = offsetY = 0;
	limitX = limitY = 0;
	screen_w = screen_h = 0;
}

void EAGrid::reset()
{
	grid = false;
	change = false;
	addX = addY = 0;
	gridX = gridY = -1;
	mouseX = mouseY = -1;

	if (!arrows.empty())
		setArrows();
}



void EAGrid::load(const float &screen_w, const float &screen_h, const int &width)
{
	free();

	this->width = width;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	offsetX = (int)((screen_w / 3) / width) * width;
	offsetY = (int)((screen_h / 3) / width) * width;
	limitX = 1500 * width;
	limitY = 1500 * width;
	
	sf::Color color = cmm::LogConsole::getLockedColor();
	color.a = 0xFF / 3;
	lineX.setSize(sf::Vector2f(1, screen_h));
	lineX.setPosition(0, 0);
	lineX.setFillColor(color);
	lineY.setSize(sf::Vector2f(screen_w, 1));
	lineY.setPosition(0, 0);
	lineY.setFillColor(color);

	suppX.setSize(sf::Vector2f(1, static_cast<float>(width) / 2));
	suppY.setSize(sf::Vector2f(static_cast<float>(width) / 2, 1));
	suppX.setFillColor(color);
	suppY.setFillColor(color);


	for (int i = 0; i < ARROWS::COUNT; ++i)
		arrows.push_back(new CircleButton);
	arrows[LEFT]->load("images/buttons/left.png");
	arrows[RIGHT]->load("images/buttons/right.png");
	arrows[TOP]->load("images/buttons/top.png");
	arrows[BOT]->load("images/buttons/bot.png");
	arrows[CENTER]->load("images/buttons/disagree.png");
	if (Loading::isError())	return;

	for (int i = 0; i < ARROWS::COUNT; ++i)
		arrows[i]->setVolume(0.0f); // muted

	for (int i = 0; i < ARROWS::COUNT; ++i)
		arrows[i]->setScale(0.25, 0.25);
	int space = static_cast<int>(screen_w / 256);
	int cirButWidth = static_cast<int>(arrows[LEFT]->getWidth());
	arrows[LEFT]->setPosition(screen_w - space * 3 - cirButWidth * 3, screen_h - cirButWidth * 2 - space);
	arrows[RIGHT]->setPosition(screen_w - space - cirButWidth, screen_h - cirButWidth * 2 - space);
	arrows[TOP]->setPosition(screen_w - space * 2 - cirButWidth * 2, screen_h - cirButWidth * 3 - space * 3);
	arrows[BOT]->setPosition(screen_w - space * 2 - cirButWidth * 2, screen_h - cirButWidth - space);
	arrows[CENTER]->setPosition(screen_w - space * 2 - cirButWidth * 2, screen_h - cirButWidth * 2 - space * 2);

	xyText.setFont(cmm::JCANDLE_FONT_PATH);
	xyText.setSize(screen_w / 80);
	xyText.setAlpha(0xFF / 3);
	xyText.setFillColor(cmm::LogConsole::getLockedColor());

	setArrows();
}

bool EAGrid::handle(const sf::Event& event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		mouseX = event.mouseMove.x;
		mouseY = event.mouseMove.y;
		setText();
	}

	for (auto &it : arrows)
		it->handle(event);

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			mouseX = event.mouseButton.x;
			mouseY = event.mouseButton.y;
			setText();
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		int code = event.key.code;

		if (code == sf::Keyboard::Left && isAbleToGoLeft())			arrows[LEFT]->setActive(true);
		else if (code == sf::Keyboard::Right && isAbleToGoRight())	arrows[RIGHT]->setActive(true);
		else if (code == sf::Keyboard::Up && isAbleToGoUp())		arrows[TOP]->setActive(true);
		else if (code == sf::Keyboard::Down && isAbleToGoDown())	arrows[BOT]->setActive(true);
	}

	for (auto &it : arrows)
		if (it->isActive())
			return true;

	return false;
}

void EAGrid::draw(sf::RenderWindow* &window)
{
	if (!grid)
	{
		lineX.setPosition(static_cast<float>(mouseX), 0.0f);
		lineY.setPosition(0.0f, static_cast<float>(mouseY));

		window->draw(lineX);
		window->draw(lineY);

		xyText.setPosition(mouseX + width / 16, mouseY - width / 8 - xyText.getHeight());
	}
	else
	{
		lineX.setPosition(static_cast<float>(gridX), 0.0f);
		lineY.setPosition(0.0f, static_cast<float>(gridY));
		window->draw(lineX);
		window->draw(lineY);

		lineX.setPosition(static_cast<float>(gridX + width), 0.0f);
		lineY.setPosition(0.0f, static_cast<float>(gridY + width));
		window->draw(lineX);
		window->draw(lineY);

		suppX.setPosition(static_cast<float>(gridX + width / 2), static_cast<float>(gridY - width / 4));
		suppY.setPosition(static_cast<float>(gridX - width / 4), static_cast<float>(gridY + width / 2));
		window->draw(suppX);
		window->draw(suppY);

		xyText.setPosition(gridX + width + 1, gridY - 1);
	}

	window->draw(xyText);

	for (auto & it : arrows)
	{
		it->draw(window);
	}
}

void EAGrid::mechanics(bool deleteMode)
{
	sf::Color color = deleteMode ? cmm::LogConsole::getErrorColor() : cmm::LogConsole::getLockedColor();
	color.a = 0xFF / 3;
	lineX.setFillColor(color);
	lineY.setFillColor(color);


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
			++count;
		}
		gridX = count * halfWidth;

		count = 0;
		int diff = static_cast <int> (screen_h) % static_cast <int> (halfWidth);
		while (gridY - diff >= halfWidth)
		{
			gridY -= halfWidth;
			++count;
		}
		gridY = count * halfWidth + diff;
	}

	checkArrows();
	setArrows();
}



const int& EAGrid::getLimitX() const
{
	return limitX;
}

const int& EAGrid::getLimitY() const
{
	return limitY;
}

const int& EAGrid::getAddX() const
{
	return addX;
}

const int& EAGrid::getAddY() const
{
	return addY;
}



int EAGrid::getX() const
{
	return grid ? gridX : mouseX;
}

int EAGrid::getY() const
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

//const bool& EAGrid::isChange() const
//{
//	return change;
//}




void EAGrid::setText()
{
	int rx = (grid ? gridX : mouseX) + (addX * -1);
	int ry = (grid ? gridY : mouseY) + addY;
	std::string result = "x: " + std::to_string((int)rx);
	result += " y: " + std::to_string((int)(ry * -1 + screen_h));
	xyText.setText(result);
}

void EAGrid::checkArrows()
{
	for (auto & it : arrows)
	{
		if (it->isActive())
		{
			change = true;
			break;
		}
	}

	if (change)
	{
		if (arrows[LEFT]->isActive())	addX += offsetX;
		if (arrows[RIGHT]->isActive())	addX -= offsetX;
		if (arrows[TOP]->isActive())	addY -= offsetY;
		if (arrows[BOT]->isActive())	addY += offsetY;
		if (arrows[CENTER]->isActive()) addX = addY = 0;
	}
}

void EAGrid::setArrows()
{
	!isAbleToGoLeft() ?	arrows[LEFT]->lock() : arrows[LEFT]->unlock();
	!isAbleToGoRight() ? arrows[RIGHT]->lock() : arrows[RIGHT]->unlock();
	!isAbleToGoUp() ? arrows[TOP]->lock() : arrows[TOP]->unlock();
	!isAbleToGoDown() ? arrows[BOT]->lock() : arrows[BOT]->unlock();
	!isAbleToCenter() ?arrows[CENTER]->lock() : arrows[CENTER]->unlock();

	for (auto & it : arrows)
		it->setActive(false);
}


// ARROWS -------------------------------------------------------------------
bool EAGrid::isAbleToGoLeft()
{
	return addX <= -offsetX;
}

bool EAGrid::isAbleToGoRight()
{
	return addX >= -limitX + offsetX;
}

bool EAGrid::isAbleToGoUp()
{
	return addY >= -limitY + offsetY;
}

bool EAGrid::isAbleToGoDown()
{
	int a = addY;
	int b = -offsetY;

	return addY <= -offsetY;
}

bool EAGrid::isAbleToCenter()
{
	return addX != 0 || addY != 0;
}