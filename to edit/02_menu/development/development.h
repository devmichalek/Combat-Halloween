/**
    development.h
    Purpose: class Development - contains develops.

    @author Adrian Michalek
    @version 2017.02.20
	@email adrmic98@gmail.com
*/

#pragma once

#include <vector>
#include "02_menu/development/develop.h"
#include "04_platform/ninja/kunai/damage.h"

class Development
{
	Damage damage;
	
	vector <Develop*> develops;
	vector <int> levels;
	vector <float> values;
	vector <float> costs;
	int bank;
	int bot;
	
	MyText skill;
	MyText level;
	MyText value;
	MyText upgrade;
	
	MyText bank_text;
	MyText money;
	
public:
	
	Development();
    ~Development();
	void free();

    void load( int bot, int screen_h );
    void draw( sf::RenderWindow* &window );
	void reloadTxt();
    void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	float multiplyCost( int which );
	
	// Other.
	void setVolume( int volume );
	void turn();
};