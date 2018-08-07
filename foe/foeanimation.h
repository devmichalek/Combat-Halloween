#pragma once
#include <vector>

class FoeAnimation
{
protected:
	int state;
	float offset;
	std::vector<int> lines;
public:
	FoeAnimation();
	virtual ~FoeAnimation();

	void setState(int newState);
	void setOffset(float newOffset);
	void setLines(std::vector<int> newLines);
	const int& getState() const;
	const float& getOffset() const;
	const std::vector<int>& getLines() const;
};