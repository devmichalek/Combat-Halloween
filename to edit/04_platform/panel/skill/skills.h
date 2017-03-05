#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "skill.h"
#include <vector>

class Skills
{
	enum
	{
		USUAL = 0,
		SLOW,
		CRITICAL,
		EXSPLOSIVE,
		SANATIVE,
		
		AMOUNT
	};
	
	MySprite grey;
	vector <MySprite*> shuriken;
	MySprite curtain;
	MyText label_one;
	vector <MyText*> label_two;
	vector <MyText*> names;
	vector <MyText*> nr;
	
	vector <Skill*> skills;
	
public:
	
	Skills();
	~Skills();
	void free();
	void reset();
	
	void load( int FPS );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0x00 );
	
	int strToInt( string s );
};