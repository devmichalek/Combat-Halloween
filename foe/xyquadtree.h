#pragma once
#include "xyquad.h"
#include "sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>


class XYQuadTree
{
	int count;
	XYQuad* root;

public:
	XYQuadTree();
	~XYQuadTree();
	bool empty();
	// void remove(XYNode* node = nullptr);
	// void remove(float x, float y, int ID);
	bool insert(XYNode* node = nullptr);
	void draw(sf::RenderWindow* &window);

	float getGreatestX();
	float getGreatestY();
	float getSmallestX();
	float getSmallestY();
	const int& getSize() const;

private:
	void free(XYQuad* quad = nullptr);
	// void removeRoot();
	// void removeMatch(XYQuad* parent = nullptr, XYQuad* match = nullptr, int dir = 0);
	// void removePrivate(XYNode* node = nullptr, XYQuad* quad = nullptr);
	bool insertPrivate(XYNode* node = nullptr, XYQuad* quad = nullptr);
	XYNode* findSmallest(XYQuad* quad = nullptr);
	XYNode* findGreatest(XYQuad* quad = nullptr);

	void findSmallestX(XYQuad* quad, float& v);
	void findGreatestX(XYQuad* quad, float& v);
	void findSmallestY(XYQuad* quad, float& v);
	void findGreatestY(XYQuad* quad, float& v);
};