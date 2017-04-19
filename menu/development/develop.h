/**
    develop.h
    Purpose: class Develop - for one special skill in menu state.

    @author Adrian Michalek
    @version 2017.02.02
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "menu/click.h"

class Develop :public Click
{
	MySprite button;
	MySprite sprite;
	MyText label;
	MyText actual;
	
	MyText name;
	MyText name_base;
	MyText cost_text;
	
	int max;
	int cost;
	int level;
	bool locked;
	
public:
	
	Develop();
    ~Develop();
	void free();

    void load( int main_x, int nr, int bot );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	bool ableToUpgrade( int bank );
	void setCost( int newcost );
	int getCost();
	int getLevel();
	
	void setActual( int level, string actual );
};