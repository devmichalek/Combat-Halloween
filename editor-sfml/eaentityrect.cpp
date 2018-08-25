#include "eaentityrect.h"

EAEntityRect::EAEntityRect()
{
	tree = nullptr;
	free();
}

EAEntityRect::~EAEntityRect()
{
	free();
}

void EAEntityRect::free()
{
	reset();
}

void EAEntityRect::reset()
{
	count = 0;

	if (tree)
	{
		delete tree;
		tree = nullptr;
	}
}

void EAEntityRect::init()
{
	tree = new RTree;
}

const std::vector<BoxID> &EAEntityRect::get(const int &addX, const int &addY, const float &screen_w, const float &screen_h)
{
	result.clear();
	Box queryBox(Point(addX, addY), Point(addX + screen_w, addY + screen_h));
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));
	return result;
}

void EAEntityRect::add(const Box &box, const int &chosen)
{
	++count;
	tree->insert(std::make_pair(box, chosen));
}

bool EAEntityRect::remove(const int &mouseX, const int &mouseY)
{
	result.clear();
	Box queryBox(Point(mouseX, mouseY), Point(mouseX + 1, mouseY + 1));
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));

	if (!result.empty())
	{
		tree->remove(result[0]);
		return true;
	}
	
	return false;
}