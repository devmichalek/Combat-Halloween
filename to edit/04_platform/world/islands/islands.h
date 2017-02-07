#pragma once

#include "hover.h"
#include "drawable/sprite.h"
#include "04_platform/world/ladder/plank.h"

class Islands
{
	int width;
	int screen_w;
	int screen_h;
	
	vector <Hover*> hovers;	// Flying islands.
	vector <Block*> blocks;	// Bottom and top islands.
	vector <Plank*> planks;	// Planks.
	vector <MySprite*> sprites;
	
public:
	
	// Basics.
	Islands();
	~Islands();
	void free();
	void reset( int distance );
	void load( int type, int width, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// Support.
	void addHover( int startX, int endX, int y, int vel );
	void addBlock( int n, int x, int y );
	void addPlank( int n, int x, int y );
	
	// Creating.
	void createFlyingIslands( vector <Block*> blocks, vector <Plank*> planks, int chance );
	void createTopIslands( vector <Block*> blocks, int w, int h );
	void createBotIslands( vector <Block*> blocks, int w, int h );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void backToGrass( int add );
	
	// Getters.
	vector <Block*> getBlocks();
	vector <Plank*> getPlanks();
	
	// Collision detection.
	bool checkCollision( Rect* rect );
	bool checkPixelCollision( Rect* rect );
};