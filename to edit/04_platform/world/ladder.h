#pragma once

#include "drawable/sprite.h"
#include "plank.h"
#include <vector>

class Ladder
{
	vector <MySprite*> ladder;
	vector <Plank*> ladders;
	
	// Color
	sf::Uint8 red, green, blue, add;
	
public:
	
	Ladder();
	~Ladder();
	void free();
	void load( int type );
	void draw( sf::RenderWindow* &window, int screen_w );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	int strToInt( string s );
	void positioning( vector <Plank*> planks );
	
	void moveX( sf::Uint8 direction, float vel );
	int backToGrass( int add );
	void addLadder( int x, int y );
	bool checkLadder( Rect* rect, int screen_w );
	
	int getW( sf::Uint8 nr );
	int getH( sf::Uint8 nr );
};