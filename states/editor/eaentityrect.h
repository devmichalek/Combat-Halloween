#pragma once
#define _SCL_SECURE_NO_WARNINGS
#include <vector>
#include "treedefinitions.h"

using IDPair = std::pair<int, int>;	// chosen + ID
using EntityRectID = std::pair<Box, IDPair>;
typedef bgi::rtree<EntityRectID, bgi::quadratic<16>> ERTree;

class EAEntityRect	// like trees, bushes (stuff with different rectlike shape)
{
	int count;
	int lastID;
	ERTree* tree;
	std::vector<EntityRectID> result;

public:
	EAEntityRect();
	~EAEntityRect();
private:
	void free();
public:
	void reset();	// empty the tree

	void init();	// builds tree
	const std::vector<EntityRectID>& get(const int &addX, const int &addY, const float &screen_w, const float &screen_h);
	bool add(const Box &box, const IDPair &idpair);
	bool remove(int &mouseX, int &mouseY);
	int getID();
};