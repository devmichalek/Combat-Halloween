#pragma once
#include "foewrapper.h"


class FoeFactory final
{
	sf::Rect<float>* resolution;
	FoeWrapper* wrapper;

public:
	FoeFactory();
	~FoeFactory();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h);
	
	void update(sf::RenderWindow* &,
				double,
				Rect* &,
				Rect* &,
				bool &,
				float &,
				float &,
				float &);

	void setBorderX(const float &newX);
	void setBorderY(const float &newY);
	void setBorders(const float &newX, const float &newY);
};