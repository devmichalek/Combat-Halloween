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
		for (unsigned i = 0; i < max; ++i)
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
		for (unsigned i = 0; i < max; ++i)
			for (unsigned j = 0; j < max; ++j)
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

void EAEntityGrid::add(const int &mouseX, const int &mouseY, const int &chosen)
{
	int x = mouseX / width;
	int y = mouseY / width;
	array[x][y] = chosen;
}

bool EAEntityGrid::remove(const int &mouseX, const int &mouseY)
{
	int x = mouseX / width;
	int y = mouseY / width;

	// Bot Right
	if (x < max && x >= 0 && y < max && y >= 0 && array[x][y] != -1)
	{
		array[x][y] = -1;
		return true;
	}

	// Bot Left
	--x;
	if (x < max && x >= 0 && y < max && y >= 0 && array[x][y] != -1)
	{
		array[x][y] = -1;
		return true;
	}

	// Top Left
	++y;
	if (x < max && x >= 0 && y < max && y >= 0 && array[x][y] != -1)
	{
		array[x][y] = -1;
		return true;
	}

	// Top Right
	++x;
	if (x < max && x >= 0 && y < max && y >= 0 && array[x][y] != -1)
	{
		array[x][y] = -1;
		return true;
	}
	
	return false;
}

const int& EAEntityGrid::getMax()
{
	return max;
}