#pragma once

#include "drawable/sprite.h"
#include <vector>

class Fireball
{
	vector <MySprite*> sprite;
	
	int offset;
	int delay;
	int line;
	int state;
	int counter;
	float counter_line;
	int fps;
	int which;
	int screen_w;
	
public:
	
	Fireball();
	~Fireball();
	void free();
	void reset();
	
	void load( int fps, int screen_w );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics( int y, sf::Uint8 direction );
	bool harmSomebody( Rect* rect );
	
	int getDamage();
	bool harmed();
};