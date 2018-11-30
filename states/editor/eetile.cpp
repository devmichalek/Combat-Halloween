#include "eetile.h"
#include "definitions.h"
#include "loading.h"

ee::Tile::Tile()
{
	array = nullptr;
	free();
}

ee::Tile::~Tile()
{
	free();
}

void ee::Tile::free()
{
	reset();

	if (array)
	{
		for (int i = 0; i < MAX_TILE_MAP_WIDTH; ++i)
		{
			delete[] array[i];
			array[i] = nullptr;
		}

		delete[] array;
		array = nullptr;
	}

	if (!sprites.empty())
	{
		for (auto &it : sprites)
		{
			delete it;
			it = nullptr;
		}

		sprites.clear();
	}

	allowDuplicates = false;
	screen = sf::Vector2f(0.0f, 0.0f);
}

void ee::Tile::reset()
{
	if (array)
		for (int i = 0; i < MAX_TILE_MAP_WIDTH; ++i)
			for (int j = 0; j < MAX_TILE_MAP_HEIGHT; ++j)
				array[i][j] = item.VOID;

	item.reset();
	active = false;
}



bool ee::Tile::checkCollision(sf::Vector2i &mouse)
{
	int x = mouse.x / TILE_WIDTH;
	int y = mouse.y / TILE_HEIGHT;

	if (x < MIN_TILE_MAP_WIDTH || x >= MAX_TILE_MAP_WIDTH || y < MIN_TILE_MAP_HEIGHT || y >= MAX_TILE_MAP_HEIGHT)
		return false;

	bool cell = array[x][y] != item.VOID;
	if ((!wholeCollision && cell) || cell)
	//{
		//mouse = sf::Vector2i(x, y);
		return true; // this cell is occupied
	//}
	else if(wholeCollision)
	{
		// check surrounding
		// 9x9 box
		//	 y
		// x|a|a|a|
		//	|a|b|b|
		//  |a|b|b|
		++x;
		--y;
		for (int i = y; i < y + 3; ++i)
		{
			if (i >= MAX_TILE_MAP_WIDTH)
				continue;

			for (int j = x; j > x - 3; --j)
			{
				if (j < MIN_TILE_MAP_HEIGHT)
					break;

				if (array[j][i] != -1)
				//{
					//mouse = sf::Vector2i(x, y);
					return true;
				//}
			}
		}
	}
	
	return false;
}

void ee::Tile::load(sf::Vector2f &screen, int amount)
{
	free();

	this->screen = screen;

	for (int i = 0; i < amount; ++i)
	{
		sprites.push_back(new cmm::Sprite());
		Loading::add(sprites[i]->load("images/platform/tiles/" + std::to_string(i) + ".png"));
		if (Loading::isError())	return;
		sprites[i]->setScale(0.51f, 0.51f);
		sprites[i]->setAlpha(MAX_ALPHA);
	}

	if (!array)
	{
		array = new char*[MAX_TILE_MAP_WIDTH];
		for (int i = 0; i < MAX_TILE_MAP_WIDTH; ++i)
			array[i] = new char[MAX_TILE_MAP_HEIGHT];
	}

	reset();
}

void ee::Tile::draw(sf::RenderWindow* &window, sf::Vector2i &add)
{
	int startX = -add.x / TILE_WIDTH;
	int endX = -add.x + static_cast<int>(screen.x / TILE_WIDTH);
	int startY = -add.y / TILE_HEIGHT;
	int endY = -add.y + static_cast<int>(screen.y / TILE_HEIGHT);
	char c;

	for (int i = startX; i < endX; ++i)
	{
		for (int j = startY; j < endY; ++j)
		{
			c = array[i][j];
			if (c != item.VOID)
			{
				sprites[c]->setPosition(i * TILE_WIDTH + add.x, ((j * TILE_HEIGHT + add.y) * -1) + screen.y - TILE_HEIGHT);
				window->draw(*sprites[c]);
			}
		}
	}
}

bool ee::Tile::add(Item &data)
{
	int x = data.position.x / TILE_WIDTH;
	int y = data.position.y / TILE_HEIGHT;

	if (x < MIN_TILE_MAP_WIDTH || x >= MAX_TILE_MAP_WIDTH || y < MIN_TILE_MAP_HEIGHT || y >= MAX_TILE_MAP_HEIGHT)
		return false; // out of range

	if (!allowDuplicates && array[x][y] != item.VOID)
		return false; // this cell is already occupied

	item.ID = item.VOID;
	item.chosen = data.chosen;
	item.type = item.TILE;
	item.ai = "";
	data.position = item.position = sf::Vector2i(x * TILE_WIDTH, y * TILE_HEIGHT);
	array[x][y] = data.chosen;
	return true;
}

bool ee::Tile::remove(sf::Vector2i &mouse)
{
	int x = mouse.x / TILE_WIDTH;
	int y = mouse.y / TILE_HEIGHT;

	if (x < MIN_TILE_MAP_WIDTH || x >= MAX_TILE_MAP_WIDTH || y < MIN_TILE_MAP_HEIGHT || y >= MAX_TILE_MAP_HEIGHT)
		return false; // out of range

	bool removed = false;

	if (array[x][y] != item.VOID)				// Bot Right
		removed = true;
	else
	{
		--x;
		if (array[x][y] != item.VOID)			// Bot Left
			removed = true;
		else
		{
			++y;
			if (array[x][y] != item.VOID)		// Top Left
				removed = true;
			else
			{
				++x;
				if (array[x][y] != item.VOID)	// Top Right
					removed = true;
			}
		}
	}

	if (removed)
	{
		item.ID = item.VOID;
		item.chosen = array[x][y];
		item.type = item.TILE;
		item.ai = "";
		mouse = item.position = sf::Vector2i(x * TILE_WIDTH, y * TILE_HEIGHT);
		array[x][y] = item.VOID;
	}

	return removed;
}