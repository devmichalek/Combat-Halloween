#pragma once

#include "drawable/sprite.h"
#include "04_platform/enemy/skeleton/skeleton.h"

class Skeleton_factory
{
	int width;
	int screen_w;
	int screen_h;
	
	vector <int> line;
	vector <int> widths;
	vector <MySprite*> sprites;
	vector <Skeleton*> skeletons;

public:
	
	// Basics.
	Skeleton_factory();
	~Skeleton_factory();
	void free();
	void reset( int distance );
	
	void load( int width, int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// Creating.
	void addSkeleton( int x, int y );
	void positioning( vector <Block*> blocks, int chance );
	
	// Collision.
	void appear( int heroX );
	void walk( int heroX, int heroY );
	bool harm( Rect* rect );
	void ableAttack( Rect* rect );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void setColor( sf::Color color );
};