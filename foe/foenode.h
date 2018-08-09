#pragma once
#include "xynode.h"
#include <SFML/Graphics/Rect.hpp>

using Rect = sf::Rect<float>;

class FoeNode: public XYNode
{
public:
	bool contains(Rect* &, Rect* &);
	virtual const int& getSpriteType() const = 0;
	virtual const int& getSpriteState() const = 0;
	virtual const int& getSpriteOffset() const = 0;
	virtual float getSpriteX() = 0;
	virtual float getSpriteY() = 0;
	virtual float getScale() = 0;

	virtual void mechanics(	double &elapsedTime,
							Rect* &character,
							Rect* &characterAttack,
							bool &characterHasAttacked,
							float &characterDamage,
							float &characterHP,
							float &characterArmour
						  ) = 0;
};