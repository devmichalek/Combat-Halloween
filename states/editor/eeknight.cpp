#include "eeknight.h"

ee::Knight::Knight()
{
	free();
}

ee::Knight::~Knight()
{
	free();
}

void ee::Knight::free()
{
	reset();
}

void ee::Knight::reset()
{
	rect.left = rect.top = -1;
}

void ee::Knight::init(const int& w, const int& h)
{
	rect.width = w;
	rect.height = h;
}

bool ee::Knight::add(const int& x, const int& y, const int& newID)
{
	rect.left = x;
	rect.top = y;
	ID = newID;
	return true;
}

bool ee::Knight::remove(int& x, int y)
{
	if (rect.contains(x, y))
	{
		//x = rect.left;
		//y = rect.top;
		add(-1, -1, ID);	// same ID
		return true;
	}
		
	return false;
}

sf::Vector2f ee::Knight::get()
{
	return sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top));
}

bool ee::Knight::isSet()
{
	return rect.left != -1 && rect.top != -1;
}

const int& ee::Knight::getID() const
{
	return ID;
}