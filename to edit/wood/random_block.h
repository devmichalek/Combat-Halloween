#pragma once

#include "templates/sprite.h"
#include "wood/block.h"
#include "wood/law.h"
#include <vector>

class Random_block
{
	int nr;
	MySprite* block;
	
	vector < vector <Law*> > rules_right;
	vector < vector <Law*> > rules_left;
	vector < vector <Law*> > rules_bot;
	vector < vector <Law*> > rules_top;
	
	int width;
	int screen_w;
	int screen_h;
	
	vector <Block*> envelope;
	
public:
	
	Random_block();
	~Random_block();
	void free();
	
	void load( int screen_w, int screen_h, int number );
	void draw( sf::RenderWindow* &window );
	void drawBG( sf::RenderWindow* &window );
	void positioning();
	
	bool checkCollision( int x, int y, int w, int h );
	int getScreenWidth();
	
	void fadein( int v = 1, int max = 255 );
	void fadeout( int v = 1, int min = 0 );
	
	void ruleRightSide();
	void ruleLeftSide();
	void ruleBotSide();
	void ruleTopSide( int number );
};