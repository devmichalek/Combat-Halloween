// @author Adrian Michalek
// @email devmichalek@gmail.com

// This template class is for all the objects inside of the game that
// Cannot be directly adjust to the game grid
// While searching the tree dismiss many quads per quad so it is really fast
// For instance we want quads in area x=0 y=0 w=1000 h=1000
// We start searching from root, then clockwise starting from left top corner to bot left corner
// If the current quad is not inside of given area we simply refuse to keep searching
// So that we dismiss a lot of data because further searching in particular quad is redundant

#pragma once

template<class Node, class Quad>
class XYQuadTree
{
protected:
	int count;
	Quad* root;

public:
	XYQuadTree();
	virtual ~XYQuadTree();
	bool empty();
	// void remove(Node* node = nullptr);
	// void remove(float x, float y, int ID);
	bool insert(Node* node = nullptr);

	float getGreatestX();
	float getGreatestY();
	float getSmallestX();
	float getSmallestY();
	const int& getSize() const;
	
private:
	void free(Quad* quad = nullptr);
	// void removeRoot();
	// void removeMatch(Quad* parent = nullptr, Quad* match = nullptr, int dir = 0);
	// void removePrivate(Node* node = nullptr, Quad* quad = nullptr);
	bool insertPrivate(Node* node = nullptr, Quad* quad = nullptr);
	// Node* findSmallest(Quad* quad = nullptr);
	// Node* findGreatest(Quad* quad = nullptr);

	void findSmallestX(Quad* quad, float& v);
	void findGreatestX(Quad* quad, float& v);
	void findSmallestY(Quad* quad, float& v);
	void findGreatestY(Quad* quad, float& v);
	// Example: bool containsPrivate(Quad* quad = nullptr, Rect* rect = nullptr);
};