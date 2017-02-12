#pragma once

#include "drawable/sprite.h"

class Torch
{
	MySprite light;
	bool active;
	
public:
	
	Torch();
	~Torch();
	void free();
	
	void load();
	void setPosition( Rect* rect );
	void drawTest( sf::RenderWindow* &window );
	
	Rect* getRect();
	sf::Image* getImage();
};