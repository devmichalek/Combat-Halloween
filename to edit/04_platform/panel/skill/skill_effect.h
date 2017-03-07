
#pragma once

#include "drawable/sprite.h"
#include <vector>

class Skill_effect
{
	int screen_w;
	int screen_h;
	
	int line;
	int vel;
	vector <float> scales;
	vector <int> alphas;
	vector <int> counters;
	vector <MySprite*> sprites;
	
public:
	
	Skill_effect();
	~Skill_effect();
	void free();
	void reset();
	
	void load( unsigned FPS, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void run( int which );
};