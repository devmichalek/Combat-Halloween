#pragma once

#include "02_menu/development/head.h"
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
	
	Headdeck();
    ~Headdeck();
	void free();

    void load( int y, int screen_h );
    void draw( sf::RenderWindow* &window );
	void reloadText();
    void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	// Other.
	void setVolume( int volume );
	void turn();
	
	// To communicate
	bool isChange();
	void setWallet( int money );
	int getWallet();
};