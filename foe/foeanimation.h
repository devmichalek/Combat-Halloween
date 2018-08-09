#pragma once
#include "foenode.h"

class FoeAnimation : virtual public FoeNode
{
protected:
	int type;
	int state;
	float offset;
	std::vector<int> lines;

	float x, y;
	float scale;
	float width;
	float left, right; // x borders

	Rect* realBox;
	Rect* attackBox;
	Rect* borderBox;

public:
	FoeAnimation();
	virtual ~FoeAnimation();

	void setSpriteType(int newType);
	// void setSpriteState(int newState);
	// void setSpriteOffset(float newOffset);
	void setSpriteLines(std::vector<int> newLines);
	const int getSpriteType() const;
	const int getSpriteState() const;
	const int getSpriteOffset() const;
	// const std::vector<int> getSpriteLines() const;
	
	void setScale(float newScale);
	void setWidth(float newWidth);
	void setPosition(float newX, float newY);
	void setBorders(float newLeft, float newRight);
	virtual void setBoxes() = 0;
	virtual float getSpriteX() = 0;
	virtual float getSpriteY() = 0;
	const float& getScaleX() const;
	float getScaleY() const;
	// const float getWidth() const;
	// const float getLeft() const;
	// const float getRight() const;

protected:
	virtual void turnLeft() = 0;
	virtual void turnRight() = 0;
	virtual bool isLeftAlign() const = 0;
	virtual bool isRightAlign() const = 0;
};