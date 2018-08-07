#pragma once
#include "xyquadtree.h"
#include <SFML/Graphics/RenderWindow.hpp>

class FoeFactory
{
	int screen_w;
	int screen_h;
	XYQuadTree* tree;

public:
	FoeFactory();
	~FoeFactory();
private:
	void free();
public:
	void reset();

	void load(float screen_w, float screen_h);
	void draw(sf::RenderWindow* &window);
	void mechanics(double elapsedTime);
};