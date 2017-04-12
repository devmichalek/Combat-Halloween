#pragma once

#include "hover.h"
#include "drawable/sprite.h"
#include "04_platform/world/brick/block.h"
#include "04_platform/enemy/actions/expletive/slab.h"

class Islands
{
	int width;
	int screen_w;
	int screen_h;
	bool moved;
	float main_vel;
	
	vector <Hover*> hovers;	// Flying islands.
	vector <Block*> blocks;	// Bottom and top islands.
	vector <Block*> planks;	// Planks.
	vector <MySprite*> sprites;
	
	Slab hit;
	
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
	void addHover( float startX, float endX, float y, float vel );
	void addBlock( int n, int x, int y );
	void addPlank( int n, int x, int y );
	
	// Creating.
	void createFlyingIslands( vector <Block*> blocks, vector <Block*> planks, int chance, float min, float max );
	void createTopIslands( vector <Block*> blocks, int w, int h, int h2 );
	void createBotIslands( vector <Block*> blocks, int w, int h );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void moveX_stand( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void setColor( sf::Color color );
	void mechanics();
	void stop( sf::Uint8 direction );
	void start();
	
	// Getters.
	vector <Block*> getBlocks();
	vector <Block*> getPlanks();
	
	// Collision detection.
	bool checkCollision( Rect* rect );
	bool checkPixelCollision( Rect* rect );
	bool checkFlyingIslands( Rect* rect );
	bool checkOtherIslands( Rect* rect );
	
	// World moving...
	void checkStands( Rect* rect );
	bool isStand();
	float getVel();
	sf::Uint8 getDirection();
	
	// Sound stuff.
	void turnOn();
	void turnOff();
	void setVolume( int v );
};