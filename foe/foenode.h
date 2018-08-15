#pragma once
#include "xynode.h"
#include <vector>
#include <SFML/Graphics/Rect.hpp>

using Rect = sf::Rect<float>;

class FoeNode: public XYNode
{
public:
	bool contains(Rect* &, Rect* &);

	virtual void setSpriteType(int newType) = 0;
	// virtual void setSpriteState(int newState) = 0;
	// virtual void setSpriteOffset(float newOffset) = 0;
	virtual void setSpriteLines(std::vector<int> newLines) = 0;
	virtual const int getSpriteType() const = 0;
	virtual const int getSpriteState() const = 0;
	virtual const int getSpriteOffset() const = 0;
	// virtual const std::vector<int> getSpriteLines() const = 0;

	virtual void setScale(float newScale) = 0;
	virtual void setWidth(float newWidth) = 0;
	virtual void setPosition(float newX, float newY) = 0;
	virtual void setBorders(float newLeft, float newRight) = 0;
	virtual void setBoxes() = 0;
	virtual float getSpriteX() = 0;
	virtual float getSpriteY() = 0;
	virtual const float& getScaleX() const = 0;
	virtual float getScaleY() const = 0;
	// virtual const float getWidth() const = 0;
	// virtual const float getLeft() const = 0;
	// virtual const float getRight() const = 0;

	virtual void turnLeft() = 0;
	virtual void turnRight() = 0;
	virtual bool isLeftAlign() const = 0;
	virtual bool isRightAlign() const = 0;

	virtual void setArmour(float newArmour) = 0;
	virtual void setDamage(float newDamage) = 0;
	virtual void setVelocity(float newVelocity) = 0;
	virtual void setHeartPoints(float newHeartPoints) = 0;
	virtual float getHPScale() = 0;

	// virtual const float getArmour() const = 0;
	// virtual const float getDamage() const = 0;
	// virtual const float getVelocity() const = 0;
	// virtual const float getHeartPoints() const = 0;
	virtual void harm(const float &value) = 0;
	virtual void setDie() = 0;

	virtual void mechanics(	double &elapsedTime,
							Rect* &character,
							Rect* &characterAttack,
							bool &characterHasAttacked,
							float &characterDamage,
							float &characterHP,
							float &characterArmour
						  ) = 0;
};