#pragma once
#include "foe.h"

class FoeAnimation : virtual public Foe
{
protected:
	int type;
	int state;
	float offset;
	std::vector<int> lines;
	float FPS;

	float x, y;
	float scale;
	float width;
	float left, right; // x borders

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


	virtual void setScale(float newScale);
	virtual void setWidth(float newWidth);
	// virtual void setHeight(float newHeight) = 0;
	virtual void setPosition(float newX, float newY);
	virtual float getSpriteX() = 0;
	virtual float getSpriteY() = 0;
	const float& getScaleX() const;
	float getScaleY() const;
	// const float getWidth() const;
	// const float getHeight();


	void setLeft(float newLeft);
	void setRight(float newRight);
	// void setTop(float newTop);
	// void setBot(float newBot);
	const float getLeft() const;
	const float getRight() const;
	const float getTop() const;
	const float getBot();


protected:
	virtual void setFPS() = 0;
	virtual void turnLeft() = 0;
	virtual void turnRight() = 0;
	virtual bool isLeftAlign() const = 0;
	virtual bool isRightAlign() const = 0;
};