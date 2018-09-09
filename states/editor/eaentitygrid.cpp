#include "eaentitygrid.h"


EAEntityGrid::EAEntityGrid()
{
	array = nullptr;
	free();
}

EAEntityGrid::~EAEntityGrid()
{
	free();
}

void EAEntityGrid::free()
{
	width = 0;
	max = 0;

	if (array)
	{
		for (int i = 0; i < max; ++i)
		{
			delete array[i];
			array[i] = nullptr;
		}

		delete array;
		array = nullptr;
	}

	reset();
}

void EAEntityGrid::reset()
{
	if (array)
		for (int i = 0; i < max; ++i)
			for (int j = 0; j < max; ++j)
				array[i][j] = -1;
}

void EAEntityGrid::init(const int& width)
{
	free();

	max = 3000;	// 3000 x 3000 = 9 000 000 possible cells
	this->width = width;

	if (!array)
	{
		array = new char*[max];
		for (int i = 0; i < max; ++i)
			array[i] = new char[max];
	}

	reset();
}

bool EAEntityGrid::isCellEmpty(const int &mouseX, const int &mouseY)
{
	return array[mouseX / width][mouseY / width] == -1;
}

char EAEntityGrid::get(const int &x, const int &y)
{
	return array[x][y];
}

bool EAEntityGrid::add(int &mouseX, int &mouseY, const int &chosen)
{
	int x = mouseX / width;
	int y = mouseY / width;

	if (array[x][y] != -1)
		return false;
	
	mouseX = x * width;
	mouseY = y * width;
	array[x][y] = chosen;
	return true;
}

int EAEntityGrid::remove(int &mouseX, int &mouseY)
{
	int x = mouseX / width;
	int y = mouseY / width;

	// Bot Right
	if (x < max && x >= 0 && y < max && y >= 0 && array[x][y] != -1)
	{
		int c = array[x][y];
		array[x][y] = -1;
		mouseX = x * width;
		mouseY = y * width;
		return c;
	}

	// Bot Left
	--x;
	if (x < max && x >= 0 && y < max && y >= 0 && array[x][y] != -1)
	{
		int c = array[x][y];
		array[x][y] = -1;
		mouseX = x * width;
		mouseY = y * width;
		return c;
	}

	// Top Left
	++y;
	if (x < max && x >= 0 && y < max && y >= 0 && array[x][y] != -1)
	{
		int c = array[x][y];
		array[x][y] = -1;
		mouseX = x * width;
		mouseY = y * width;
		return c;
	}

	// Top Right
	++x;
	if (x < max && x >= 0 && y < max && y >= 0 && array[x][y] != -1)
	{
		int c = array[x][y];
		array[x][y] = -1;
		mouseX = x * width;
		mouseY = y * width;
		return c;
	}
	
	return -1;
}

const int& EAEntityGrid::getMax()
{
	return max;
}