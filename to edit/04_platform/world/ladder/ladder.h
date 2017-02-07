#pragma once

#include "drawable/sprite.h"
#include "plank.h"
#include <vector>

class Ladder
{
	int width;
	int screen_w;
	
	vector <Plank*> planks;
	vector <MySprite*> sprites;
	
	// Color
	sf::Uint8 red, green, blue, add;
	
public:
	
	// Basics.
	Ladder();
	~Ladder();
	void free();
	void reset( int distance );
	void load( int type, int width, int screen_w );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// Support.
	int to_int( string s );
	
	// Setter.
	void positioning( vector <Plank*> planks );
	
	// In action.
	void moveX( sf::Uint8 direction, float vel );
	void backToGrass( int add );
	
	// Getters.
	int getW( sf::Uint8 nr );
	int getH( sf::Uint8 nr );
	
	// Check collision.
	bool checkCollision( Rect* rect );
};