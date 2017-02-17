#pragma once

#include "drawable/sprite.h"
#include "04_platform/enemy/skeleton/skeleton.h"

class Skeleton_factory
{
	int width;
	int screen_w;
	int screen_h;
	
	// life stuff
	MySprite life;
	MySprite frame;
	
	vector <Skeleton*> ::iterator sword;
	vector <sf::Uint8> line;
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
	void addSkeleton( int x, int y, int damage );
	void positioning( vector <Block*> blocks, int chance );
	
	// Collision.
	void appear( Rect* rect );
	void walk( Rect* rect );
	bool harm( Rect* rect, int damage );
	void ableAttack( Rect* rect );
	bool isSword( Rect* rect );
	int getDamage();
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setColor( sf::Color color );
	
	// Connecting with other life
	unsigned getSize();
	Rect* getRect( int which );
	void harmDefinite( int which, int damage );
};