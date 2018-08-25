#define _SCL_SECURE_NO_WARNINGS
#pragma once
#include <vector>
#include "treedefinitions.h"

class EAEntityRect	// like trees, bushes (stuff with different rect shape)
{
	int count;
	RTree* tree;
	std::vector<BoxID> result;

public:
	EAEntityRect();
	~EAEntityRect();
private:
	void free();
public:
	void reset();	// empty the tree

	void init();	// builds tree
	const std::vector<BoxID> &get(const int &addX, const int &addY, const float &screen_w, const float &screen_h);
	void add(const Box &box, const int &chosen);
	bool remove(const int &mouseX, const int &mouseY);
};