#pragma once
#include <vector>
#include <SFML/Graphics/Rect.hpp>

using Rect = sf::Rect<float>;

// Each foe has to override these functions
class Foe
{
public:
	virtual void setSpriteType(int newType) = 0;				// Skeleton / Zombie / Vampire...
	// virtual void setSpriteState(int newState) = 0;			// Appear / Idle / Attack ...
	// virtual void setSpriteOffset(float newOffset) = 0;		// 0 ... n ...
	virtual void setSpriteLines(std::vector<int> newLines) = 0;	// Appear -> 7 ... State -> n
	virtual const int getSpriteType() const = 0;
	virtual const int getSpriteState() const = 0;
	virtual const int getSpriteOffset() const = 0;
	// virtual const std::vector<int> getSpriteLines() const = 0;


	virtual void setScale(float newScale) = 0;
	virtual void setWidth(float newWidth) = 0;
	// virtual void setHeight(float newHeight) = 0;
	virtual void setPosition(float newX, float newY) = 0;	// Start position.
	virtual float getSpriteX() = 0;
	virtual float getSpriteY() = 0;
	virtual const float& getScaleX() const = 0;
	virtual float getScaleY() const = 0;
	// virtual const float getWidth() const = 0;
	// virtual const float getHeight() const = 0;


	virtual void setLeft(float newLeft) = 0;
	virtual void setRight(float newRight) = 0;
	// virtual void setTop(float newTop) = 0;
	// virtual void setBot(float newBot) = 0;
	virtual const float getLeft() const = 0;
	virtual const float getRight() const = 0;
	virtual const float getTop() const = 0;
	virtual const float getBot() = 0;


	virtual void mechanics(	double &elapsedTime,
							Rect* &character,
							Rect* &characterAttack,
							bool &characterHasAttacked,
							float &characterDamage,
							float &characterHP,
							float &characterArmour) = 0;

	virtual float getHPScale() = 0;
	virtual void marshial() = 0;	// Call it at the end to form foe!
	virtual void setFeatures(std::vector<std::string> features) = 0;	// Armour / Velocity... it's unique
};