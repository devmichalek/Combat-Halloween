/**
    headdeck.h
    Purpose: class Headdeck - bunch of heads

    @author Adrian Michalek
    @version 2017.04.11
	@email adrmic98@gmail.com
*/

#pragma once

#include "menu/development/head.h"
#include <vector>

class Headdeck
{
	enum
	{
		TYPE = 0,
		SPECS,
		COST,
		WALLET,
		MONEY,
		AMOUNT
	};
	
	int wallet;
	bool change;
	MySprite line;
	vector <MyText*> texts;
	vector <Head*> heads;
	
public:
	
	// Basics.
	Headdeck();
    ~Headdeck();
	void free();
	
	void load( unsigned screen_w, unsigned screen_h, float y );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	// Other.
	void reloadText();
	void setVolume( int volume );
	void turn();
	void turnOn();
	void turnOff();
	
	// To communicate
	bool isChange();
	void setWallet( int money );
	int getWallet();
};