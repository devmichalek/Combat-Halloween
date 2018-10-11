#include "eetile.h"
#include "definitions.h"

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

	reset();
}

void ee::Tile::reset()
{
	if (array)
		for (int i = 0; i < MAX_TILE_MAP_WIDTH; ++i)
			for (int j = 0; j < MAX_TILE_MAP_HEIGHT; ++j)
				array[i][j] = -1;
}

void ee::Tile::init()
{
	free();

	if (!array)
	{
		array = new char*[MAX_TILE_MAP_WIDTH];
		for (int i = 0; i < MAX_TILE_MAP_WIDTH; ++i)
			array[i] = new char[MAX_TILE_MAP_HEIGHT];
	}

	reset();
}

char ee::Tile::get(const int &x, const int &y)
{
	return array[x][y];
}

bool ee::Tile::add(int &mouseX, int &mouseY, const int &chosen)
{
	int x = mouseX / TILE_WIDTH;
	int y = mouseY / TILE_HEIGHT;

	if (x < MIN_TILE_MAP_WIDTH || x >= MAX_TILE_MAP_WIDTH || y < MIN_TILE_MAP_HEIGHT || y >= MAX_TILE_MAP_HEIGHT)
		return false;

	if (array[x][y] != -1)
		return false;
	
	mouseX = x * TILE_WIDTH;
	mouseY = y * TILE_HEIGHT;
	array[x][y] = chosen;
	return true;
}

int ee::Tile::remove(int &mouseX, int &mouseY)
{
	int x = mouseX / TILE_WIDTH;
	int y = mouseY / TILE_HEIGHT;

	// Bot Right
	if (x < MAX_TILE_MAP_WIDTH && x >= MIN_TILE_MAP_WIDTH && y < MAX_TILE_MAP_HEIGHT && y >= MIN_TILE_MAP_HEIGHT && array[x][y] != -1)
	{
		int c = array[x][y];
		array[x][y] = -1;
		mouseX = x * TILE_WIDTH;
		mouseY = y * TILE_HEIGHT;
		return c;
	}

	// Bot Left
	--x;
	if (x < MAX_TILE_MAP_WIDTH && x >= MIN_TILE_MAP_WIDTH && y < MAX_TILE_MAP_HEIGHT && y >= MIN_TILE_MAP_HEIGHT && array[x][y] != -1)
	{
		int c = array[x][y];
		array[x][y] = -1;
		mouseX = x * TILE_WIDTH;
		mouseY = y * TILE_HEIGHT;
		return c;
	}

	// Top Left
	++y;
	if (x < MAX_TILE_MAP_WIDTH && x >= MIN_TILE_MAP_WIDTH && y < MAX_TILE_MAP_HEIGHT && y >= MIN_TILE_MAP_HEIGHT && array[x][y] != -1)
	{
		int c = array[x][y];
		array[x][y] = -1;
		mouseX = x * TILE_WIDTH;
		mouseY = y * TILE_HEIGHT;
		return c;
	}

	// Top Right
	++x;
	if (x < MAX_TILE_MAP_WIDTH && x >= MIN_TILE_MAP_WIDTH && y < MAX_TILE_MAP_HEIGHT && y >= MIN_TILE_MAP_HEIGHT && array[x][y] != -1)
	{
		int c = array[x][y];
		array[x][y] = -1;
		mouseX = x * TILE_WIDTH;
		mouseY = y * TILE_HEIGHT;
		return c;
	}
	
	return -1;
}

bool ee::Tile::checkCollision(sf::Rect<int> rect)
{
	int x = rect.left / TILE_WIDTH;
	int y = rect.top / TILE_HEIGHT;

	if (x < MIN_TILE_MAP_WIDTH || x >= MAX_TILE_MAP_WIDTH || y < MIN_TILE_MAP_HEIGHT || y >= MAX_TILE_MAP_HEIGHT)
		return false;

	bool currentCell = array[x][y] != -1;
	if ((!collision && currentCell) || currentCell)
	{
		return true; // this cell is occupied
	}
	else if(collision)
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
				if (j < 0)
					break;

				if (array[j][i] != -1)
					return true;
			}
		}
	}
	
	return false;
}