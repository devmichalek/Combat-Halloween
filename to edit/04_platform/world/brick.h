#pragma once

#include "drawable/sprite.h"
#include "04_platform/ladder/plank.h"
#include "rules.h"
#include "moving_block.h"

class Brick
{
	string info;
	int16_t width;
	int16_t screen_w;
	int16_t screen_h;
	
	int left;	// The smallest x.
	int right;	// The biggest y.
	
	vector <int>::size_type size;
	vector <Plank*> planks;
	vector <Block*> blocks;
	vector <MySprite*> sprites;
	vector <Moving_block*> moving_blocks;
	
	int fallenX;			// Distance to make after hero fall.
	int grass_value;		// Velocity (1,-1,0) for other objects.
	vector <Block*>::iterator lastGrass;	// Contain number of last grass standingby hero block.
	unsigned water_line;	// Line between water and other blocks (islands + basic).
	unsigned islands_line;	// Line between islands and other blocks (basic).
	
	
public:

	// Changing size.
	void reserve( unsigned size );	// Estimate size then reserve.
	void shrink();					// Shrink to fit.
	
	// Basics.
	Brick();
	~Brick();
	void free();
	int reset();
	void load( int screen_w, int screen_h, int type );
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
	void createMovingIslands();							// Add moving islands.
	void createLeftBorders();							// Add left borders to hills.
	void createRightBorders();							// Add right borders to hills.
	void createStuffing( int a, int n );				// Fill hills.
	void createTopIslands( int w, int h );				// Add top islands.
	void createBotIslands( int w, int h );				// Add bot islands.
	void createWater();									// Add water.
	
	// Setters
	void setLeft();		// set the smallest x.
	void setRight(); 	// set the biggest x.
	
	
	sf::Uint8 moveX( sf::Uint8 direction, float vel );	// Move whether hero moves.
	void findLastGrass( Rect* rect );	// Find last standing grass block.
	void setNewX( int heroX );			// Set new x every fall (fallenX).
	bool backToGrass();					// After new fallenX move blocks and send message about it.
	
	
	// Getters.
	int getLastGrassX();	// Get x from last grass block.
	int getLastGrassY();	// Get y from last grass block.
	int getGrassValue();	// Get velocity (for other objects to tell when they have to move).
	sf::Uint8 getWidth();	// Get width of divide.
	vector <Block*> getBlocks();
	vector <Plank*> getPlanks();
	int getLeft();
	int getRight();
	
	
	// Collision detection.
	bool checkCollision( Rect* rect );
	bool checkPixelCollision( Rect* rect );
	bool isInTheWater( Rect* rect );
};

