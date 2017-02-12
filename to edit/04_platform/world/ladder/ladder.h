#pragma once

#include "drawable/sprite.h"
#include "04_platform/world/brick/block.h"
#include <vector>

class Ladder
{
	int width;
	int screen_w;
	
	vector <Block*> planks;
	vector <MySprite*> sprites;
	
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
	void positioning( vector <Block*> planks );
	void shrink();
	
	// In action.
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void setColor( sf::Color color );
	
	// Getters.
	int getW( sf::Uint8 nr );
	int getH( sf::Uint8 nr );
	
	// Check collision.
	bool checkCollision( Rect* rect );
};