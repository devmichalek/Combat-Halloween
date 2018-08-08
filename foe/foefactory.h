#pragma once
#include "foetree.h"


class FoeFactory
{
	sf::Rect<float> res;		// resolution of the window
	sf::Rect<float> resBulk;	// resolution + window width and window height are doubled
	FoeTree* tree;

public:
	FoeFactory();
	~FoeFactory();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

	void setBorderX(const float &newX);
	void setBorderY(const float &newY);
	void setBorders(const float &newX, const float &newY);
};