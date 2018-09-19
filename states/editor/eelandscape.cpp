#include "eelandscape.h"

ee::Landscape::Landscape()
{
	tree = nullptr;
	free();
}

ee::Landscape::~Landscape()
{
	free();
}

void ee::Landscape::free()
{
	reset();
}

void ee::Landscape::reset()
{
	count = 0;
	lastID = -1;

	if (tree)
	{
		delete tree;
		tree = nullptr;
	}
}

void ee::Landscape::init()
{
	tree = new LandscapeTree;
}

const std::vector<ee::LandscapeBox> &ee::Landscape::get(const int &addX, const int &addY, const float &screen_w, const float &screen_h)
{
	result.clear();
	Box queryBox(Point(addX, addY), Point(addX + screen_w, addY + screen_h));
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));
	return result;
}

bool ee::Landscape::add(const Box &box, const LandscapeEntity &le)
{
	++count;
	tree->insert(std::make_pair(box, le));
	return true;
}

bool ee::Landscape::remove(int &mouseX, int &mouseY)
{
	result.clear();
	Box queryBox(Point(mouseX, mouseY), Point(mouseX + 1, mouseY + 1));
	tree->query(bgi::intersects(queryBox), std::back_inserter(result));

	if (!result.empty())
	{
		//mouseX = bg::get<0>(result[0].first.min_corner());
		//mouseX = bg::get<1>(result[0].first.min_corner());
		tree->remove(result[0]);
		lastID = result[0].second.id;
		return true;
	}
	
	return false;
}

int ee::Landscape::getID()
{
	int ID = lastID;
	lastID = -1;

	return ID;
}