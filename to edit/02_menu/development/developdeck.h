/**
    development.h
    Purpose: class Development - contains develops.

    @author Adrian Michalek
    @version 2017.02.20
	@email adrmic98@gmail.com
*/

#pragma once

#include "02_menu/development/develop.h"
#include "04_platform/ninja/kunai/damage.h"
#include <vector>

class Development
{
	enum
	{
		SKILL = 0,
		LEVEL,
		VALUE,
		UPGRADE,
		WALLET,
		MONEY,
		AMOUNT
	};
	
	int bot;
	int wallet;
	bool change;
	
	MySprite line;
	vector <MyText*> texts;
	vector <Develop*> develops;
	vector <int> levels;
	vector <float> costs;
	vector <float> values;
	
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
	
	// To communicate
	bool isChange();
	void setWallet( int money );
	int getWallet();
};