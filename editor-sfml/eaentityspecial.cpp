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

void EAEntitySpecial::init(const float& w, const float& h)
{
	rect.width = w;
	rect.height = h;
}

void EAEntitySpecial::add(const float& x, const float& y)
{
	rect.left = x;
	rect.top = y;
}

bool EAEntitySpecial::remove(const float& x, const float& y)
{
	if (rect.contains(x, y + rect.height))
	{
		add(-1, -1);
		return true;
	}
		
	return false;
}

sf::Vector2f EAEntitySpecial::get()
{
	return sf::Vector2f(rect.left, rect.top);
}

bool EAEntitySpecial::isSet()
{
	return rect.left != -1 && rect.top != -1;
}