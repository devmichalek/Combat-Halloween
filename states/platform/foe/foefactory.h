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
	
	void update(sf::RenderWindow* &window,
				double elapsedTime,
				Rect* &character,
				Rect* &characterAttack,
				bool &characterHasAttacked,
				float &characterDamage,
				float &characterHP,
				float &characterArmour,
				float &newX,
				float &newY
				);
};