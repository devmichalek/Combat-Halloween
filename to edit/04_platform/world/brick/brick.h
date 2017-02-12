#pragma once

#include "drawable/sprite.h"
#include "04_platform/world/brick/block.h"
#include "rules.h"

class Brick
{
	int width;
	int screen_w;
	int screen_h;
	
	int left;	// The smallest x.
	int right;	// The biggest y.
	
	vector <int>::size_type size;
	vector <Block*> planks;
	vector <Block*> blocks;
	vector <MySprite*> sprites;
	
	int grass_distance;
	sf::Uint8 grass_value;
	
public:

	// Changing size.
	void reserve( unsigned size );	// Estimate size then reserve.
	void shrink();					// Shrink to fit.
	
	// Basics.
	Brick();
	~Brick();
	void free();
	int reset();
	void load( int type, int width, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// Support.
	int to_int( string s );						// Transform string into int.
	void addPlank( int n, int x, int y );
	void addBlock( int n, int x, int y );
	sf::Uint8 getNewFloor( sf::Uint8 floor, int chance );	// For createTopBorders() function to decide about new floor.
	
	// Creators in appriopriate order.
	void createTopBorders( int size, int chance, int w, int h );	// Add main path - important.
	void createLeftBorders();							// Add left borders to hills.
	void createRightBorders();							// Add right borders to hills.
	void createStuffing( int a, int n );				// Fill hills.
	
	// Setters
	void setLeft();		// set the smallest x.
	void setRight(); 	// set the biggest x.
	
	// In action.
	sf::Uint8 moveX( sf::Uint8 direction, float vel );	// Move whether hero moves.
	int getNearGrassY( int hero_x );
	int getGrassDistance();
	sf::Uint8 getGrassValue();
	void undoFall();
	void setColor( sf::Color color );
	
	// Getters.
	sf::Uint8 getWidth();	// Get width of divide.
	vector <Block*> getBlocks();
	vector <Block*> getPlanks();
	int getLeft();
	int getRight();
	
	
	// Collision detection.
	bool checkCollision( Rect* rect );
	bool checkPixelCollision( Rect* rect );
	void checkTorch( Rect* rect, sf::Image* image );
};

