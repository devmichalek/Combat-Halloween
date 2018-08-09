#include "foeanimation.h"

FoeAnimation::FoeAnimation()
{
	type = -1;
	state = -1;
	offset = 0;

	x = y = 0;
	scale = 0;
	width = 0;
	left = right = 0;
}

FoeAnimation::~FoeAnimation()
{
	type = -1;
	state = -1;
	offset = 0;
	if (!lines.empty())
	{
		lines.clear();
		lines.shrink_to_fit();
	}

	x = y = 0;
	scale = 0;
	width = 0;
	left = right = 0;
}

void FoeAnimation::setSpriteType(int newType)
{
	type = newType;
}
/*
void FoeAnimation::setSpriteState(int newState)
{
	state = newState;
}

void FoeAnimation::setSpriteOffset(float newOffset)
{
	offset = newOffset;
}
*/
void FoeAnimation::setSpriteLines(std::vector<int> newLines)
{
	lines = newLines;
}

const int FoeAnimation::getSpriteType() const
{
	return type;
}

const int FoeAnimation::getSpriteState() const
{
	return state;
}

const int FoeAnimation::getSpriteOffset() const
{
	return offset;
}
/*
const std::vector<int> FoeAnimation::getSpriteLines() const
{
	return lines;
}
*/


void FoeAnimation::setScale(float newScale)
{
	scale = newScale;
}

void FoeAnimation::setWidth(float newWidth)
{
	width = newWidth;
}

void FoeAnimation::setPosition(float newX, float newY)
{
	x = newX;
	y = newY;
}

void FoeAnimation::setBorders(float newLeft, float newRight)
{
	left = newLeft;
	right = newRight;
}

const float& FoeAnimation::getScaleX() const
{
	return scale;
}

float FoeAnimation::getScaleY() const
{
	return scale < 0 ? -scale : scale;
}
/*
const float FoeAnimation::getWidth() const
{
	return width;
}

const float FoeAnimation::getLeft() const
{
	return left;
}

const float FoeAnimation::getRight() const
{
	return right;
}
*/