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
	lastID = -1;

	if (tree)
	{
		delete tree;
		tree = nullptr;
	}
}

void EAEntityRect::init()
{
	tree = new ERTree;
}

const std::vector<EntityRectID> &EAEntityRect::get(const int &addX, const int &addY, const float &screen_w, const float &screen_h)
{
	result.clear();
	Box queryBox(Point(addX, addY), Point(addX + screen_w, addY + screen_h));
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));
	return result;
}

bool EAEntityRect::add(const Box &box, const IDPair &idpair)
{
	++count;
	tree->insert(std::make_pair(box, idpair));
	return true;
}

bool EAEntityRect::remove(int &mouseX, int &mouseY)
{
	result.clear();
	Box queryBox(Point(mouseX, mouseY), Point(mouseX + 1, mouseY + 1));
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));

	if (!result.empty())
	{
		mouseX = bg::get<0>(result[0].first.min_corner());
		mouseX = bg::get<1>(result[0].first.min_corner());
		tree->remove(result[0]);
		lastID = result[0].second.first;
		return true;
	}
	
	return false;
}

int EAEntityRect::getID()
{
	int ID = lastID;
	lastID = -1;

	return ID;
}