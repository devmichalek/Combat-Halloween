#pragma once

#include "drawable/sprite.h"
#include "plank.h"

class Brick
{
	int16_t width;
	int16_t screen_w;
	int16_t screen_h;
	
	int left;
	int right;
	
	vector <Plank*> planks;
	vector <Block*> blocks;
	vector <MySprite*> sprites;
	
	int fallenX;
	unsigned lastGrass;
	unsigned water_line;
	unsigned islands_line;
	
public:
	
	// Basics.
	Brick();
	~Brick();
	void free();
	void load( int screen_w, int screen_h, int type );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// Support.
	int to_int( string s );
	void addPlank( int n, int x, int y );
	void addBlock( int n, int x, int y );
	sf::Uint8 getNewFloor( sf::Uint8 floor );
	
	// Creators.
	void createTopBorders( int size, int w, int h );
	void createLeftBorders();
	void createRightBorders();
	void createStuffing( int a, int n );	//  Fill from left to right.
	void createTopIslands( int w, int h );
	void createBotIslands( int w, int h );
	void createWater();
	
	// Setters
	void setLeft();		// set the smallest x.
	void setRight(); 	// set the biggest x.
	
	
	sf::Uint8 moveX( sf::Uint8 direction, float vel );
	void findLastGrass( Rect* rect );
	void setNewX( int heroX );
	int backToGrass();
	
	
	// Getters.
	int getLastGrassX();
	int getLastGrassY();
	sf::Uint8 getWidth();
	vector <Block*> getBlocks();
	vector <Plank*> getPlanks();
	
	
	// Check collision.
	bool checkCollision( Rect* rect );
	bool checkBlockByPixel( Rect* rect );
};

