#pragma once

#include "drawable/sprite.h"
#include "04_platform/enemy/actions/hp_dots/hp_dot.h"
#include "04_platform/world/brick/block.h"
#include <vector>

using namespace std;

class Score_dots
{
	int screen_w;
	int main_alpha;
	MySprite sprite;
	vector <Hp_dot*> dots;
	
public:
	
	Score_dots();
	~Score_dots();
	void free();
	void reset( int distance );
	
	void load( int screen_w );
	void draw( sf::RenderWindow* &window );
	void positioning( int chance, vector <Block*> blocks, int width );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// In action
	void moveX( sf::Uint8 d, float v );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setAlpha( int alpha );
	
	bool uplift( Rect* rect );
};