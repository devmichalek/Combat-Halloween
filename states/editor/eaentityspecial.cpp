#include "eaentityspecial.h"

EAEntitySpecial::EAEntitySpecial()
{
	free();
}

EAEntitySpecial::~EAEntitySpecial()
{
	free();
}

void EAEntitySpecial::free()
{
	reset();
}

void EAEntitySpecial::reset()
{
	rect.left = rect.top = -1;
}

void EAEntitySpecial::init(const int& w, const int& h)
{
	rect.width = w;
	rect.height = h;
}

bool EAEntitySpecial::add(const int& x, const int& y, const int& newID)
{
	rect.left = x;
	rect.top = y;
	ID = newID;
	return true;
}

bool EAEntitySpecial::remove(int& x, int& y)
{
	if (rect.contains(x, y))
	{
		x = rect.left;
		y = rect.top;
		add(-1, -1, ID);	// same ID
		return true;
	}
		
	return false;
}

sf::Vector2f EAEntitySpecial::get()
{
	return sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top));
}

bool EAEntitySpecial::isSet()
{
	return rect.left != -1 && rect.top != -1;
}

const int& EAEntitySpecial::getID() const
{
	return ID;
}