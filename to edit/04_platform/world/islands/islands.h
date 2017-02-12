#pragma once

#include "hover.h"
#include "drawable/sprite.h"
#include "04_platform/world/brick/block.h"

class Islands
{
	int width;
	int screen_w;
	int screen_h;
	bool moved;
	
	vector <Hover*> hovers;	// Flying islands.
	vector <Block*> blocks;	// Bottom and top islands.
	vector <Block*> planks;	// Planks.
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
	void createFlyingIslands( vector <Block*> blocks, vector <Block*> planks, int chance );
	void createTopIslands( vector <Block*> blocks, int w, int h, int h2 );
	void createBotIslands( vector <Block*> blocks, int w, int h );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void setColor( sf::Color color );
	void moving();
	void turnOff( sf::Uint8 direction );
	void turnOn();
	
	// Getters.
	vector <Block*> getBlocks();
	vector <Block*> getPlanks();
	
	// Collision detection.
	bool checkCollision( Rect* rect );
	bool checkPixelCollision( Rect* rect );
	bool checkFlyingIslands( Rect* rect );
	bool checkOtherIslands( Rect* rect );
};