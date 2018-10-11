#include "eagrid.h"
#include "loading.h"
#include "definitions.h"

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

	offsetX = offsetY = 0;
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



void EAGrid::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;
	offsetX = (int)((screen_w / 3) / TILE_FULL_WIDTH) * TILE_FULL_WIDTH;
	offsetY = (int)((screen_h / 3) / TILE_FULL_WIDTH) * TILE_FULL_WIDTH;
	
	sf::Color color = cmm::LOCKED_COLOR;
	color.a = (int)MAX_ALPHA / 3;
	lineX.setSize(sf::Vector2f(1, screen_h));
	lineX.setPosition(0, 0);
	lineX.setFillColor(color);
	lineY.setSize(sf::Vector2f(screen_w, 1));
	lineY.setPosition(0, 0);
	lineY.setFillColor(color);

	suppX.setSize(sf::Vector2f(1, static_cast<float>(TILE_WIDTH)));
	suppY.setSize(sf::Vector2f(static_cast<float>(TILE_WIDTH), 1));
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
		arrows[i]->setVolume(MIN_SOUND_VOLUME); // muted

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
	xyText.setAlpha(MAX_ALPHA / 3);
	xyText.setFillColor(cmm::LOCKED_COLOR);

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

		xyText.setPosition(mouseX + TILE_WIDTH / 8, mouseY - TILE_WIDTH / 4 - xyText.getHeight());
	}
	else
	{
		lineX.setPosition(static_cast<float>(gridX), 0.0f);
		lineY.setPosition(0.0f, static_cast<float>(gridY));
		window->draw(lineX);
		window->draw(lineY);

		lineX.setPosition(static_cast<float>(gridX + TILE_FULL_WIDTH), 0.0f);
		lineY.setPosition(0.0f, static_cast<float>(gridY + TILE_FULL_WIDTH));
		window->draw(lineX);
		window->draw(lineY);

		suppX.setPosition(static_cast<float>(gridX + TILE_WIDTH), static_cast<float>(gridY - TILE_WIDTH / 2));
		suppY.setPosition(static_cast<float>(gridX - TILE_WIDTH / 2), static_cast<float>(gridY + TILE_WIDTH));
		window->draw(suppX);
		window->draw(suppY);

		xyText.setPosition(gridX + TILE_FULL_WIDTH + 1, gridY - 1);
	}

	window->draw(xyText);

	for (auto & it : arrows)
	{
		it->draw(window);
	}
}

void EAGrid::mechanics(bool deleteMode)
{
	sf::Color color = deleteMode ? cmm::ERROR_COLOR : cmm::LOCKED_COLOR;
	color.a = (int)MAX_ALPHA / 3;
	lineX.setFillColor(color);
	lineY.setFillColor(color);


	// Calculate grid
	if (grid)
	{
		gridX = mouseX;
		gridY = mouseY;

		int count = 0;
		while (gridX >= TILE_WIDTH)
		{
			gridX -= TILE_WIDTH;
			++count;
		}
		gridX = count * TILE_WIDTH;

		count = 0;
		int diff = static_cast <int> (screen_h) % static_cast <int> (TILE_WIDTH);
		while (gridY - diff >= TILE_WIDTH)
		{
			gridY -= TILE_WIDTH;
			++count;
		}
		gridY = count * TILE_WIDTH + diff;
	}

	checkArrows();
	setArrows();
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
	return addX >= -MAX_MAP_WIDTH + offsetX;
}

bool EAGrid::isAbleToGoUp()
{
	return addY >= -MAX_MAP_HEIGHT + offsetY;
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