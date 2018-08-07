#include "foeanimation.h"

FoeAnimation::FoeAnimation()
{
	state = -1;
	offset = 0;
}

FoeAnimation::~FoeAnimation()
{
	state = -1;
	offset = 0;
	if (!lines.empty())
	{
		lines.clear();
		lines.shrink_to_fit();
	}
}



void FoeAnimation::setState(int newState)
{
	state = newState;
}

void FoeAnimation::setOffset(float newOffset)
{
	offset = newOffset;
}

void FoeAnimation::setLines(std::vector<int> newLines)
{
	lines = newLines;
}

const int& FoeAnimation::getState() const
{
	return state;
}

const float& FoeAnimation::getOffset() const
{
	return offset;
}

const std::vector<int>& FoeAnimation::getLines() const
{
	return lines;
}