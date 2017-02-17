#pragma once

#include "drawable/sprite.h"
#include <vector>

class Heart
{
	int max;
	vector <MySprite*> fill;
	vector <MySprite*> frame;
	vector <MySprite*> grey_panel;
	
	bool flag;
	int life;
	
public:
	
	Heart();
	~Heart();
	void free();
	
	void load();
	void draw( sf::RenderWindow* &window );
	void setLife( int chance );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0x00 );
	
	void harm( int damage );
	bool isDead();
	void reset();
};