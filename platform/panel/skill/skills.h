/**
    skills.h
    Purpose: class Skills as a skills panel in play state.

    @author Adrian Michalek
    @version 2016.03.06
	@email adrmic98@gmail.com
*/

#pragma once

#include "skill_effect.h"
#include "skill.h"
#include "drawable/sprite.h"
#include "drawable/text.h"
#include <vector>
#include <stack>

class Skills
{
	enum
	{
		USUAL = 0,
		SWORD,
		SLOW,
		CRITICAL,
		EXSPLOSIVE,
		SANATIVE,
		AMOUNT
	};

	
	MySprite grey;
	vector <MySprite*> pictures;
	MySprite curtain;
	MyText label_one;
	vector <MyText*> label_two;
	vector <MyText*> names;
	vector <MyText*> nr;
	
	vector <Skill*> skills;
	stack <int> actions;
	vector <int> levels;
	vector <bool> gold;
	Skill_effect skill_effect;
	
public:
	
	Skills();
	~Skills();
	void free();
	void reset();
	
	void load( unsigned FPS, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0x00 );
	
	int getTop();
	bool isHeal();
	void swordUsed();
	void mechanics();
};