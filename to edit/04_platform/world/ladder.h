#pragma once

#include "drawable/sprite.h"
#include "plank.h"
#include <vector>

class Ladder
{
	vector <Plank*> planks;
	vector <MySprite*> sprites;
	
	// Color
	sf::Uint8 red, green, blue, add;
	
public:
	
	Ladder();
	~Ladder();
	void free();
	void reset( int distance );
	void load( int type );
	void draw( sf::RenderWindow* &window, int screen_w );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	int to_int( string s );
	void positioning( vector <Plank*> planks );
	
	void moveX( sf::Uint8 direction, float vel );
	void backToGrass( int add );
	bool checkCollision( Rect* rect, int screen_w );
	
	int getW( sf::Uint8 nr );
	int getH( sf::Uint8 nr );
};