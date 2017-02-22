#pragma once

#include "04_platform/world/brick/block.h"
#include "drawable/sprite.h"
#include "drawable/text.h"
#include <vector>
#include "02_menu/click.h"

using namespace std;

template <typename F>
class Factory
{
	enum
	{
		DELAY = 0,
		SCALE,
		DAMAGE,
		VEL,
		HP,
		AL,
		AMOUNT
	};
	
	int width;
	int screen_w;
	int screen_h;
	
	typename vector <F*> ::iterator sword;
	vector <sf::Uint8> lines;
	vector <MySprite*> sprites;
	vector <F*> foes;
	vector <vector <tuple <int, int, float> >> m;
	vector <float> features;
	
	MyText hp;
	vector <Click*> hits;

public:

	// Constructor, destructor.
	Factory();
	~Factory();
	
	// Free, reset.
	void free();
	void reset( int distance );
	
	// Load, draw, fadein, fadeout.
	void load( int width, int screen_w, int screen_h, string name );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// Creating.
	void deallocate();
	int strToInt( string s );
	void add( int x, int y, int chance );
	void positioning( vector <Block*> blocks, int chance );
	
	// Collision stuff.
	void appear( Rect* rect );
	void walk( Rect* rect );
	bool harm( Rect* rect, int damage );
	void ableAttack(  Rect* rect );
	bool harmSomebody( Rect* rect );
	
	// Get particular damage.
	int getDamage();
	
	// In action
	void moveX_Group( sf::Uint8 direction, float vel );
	void undoFall_Group( sf::Uint8 add );
	void mechanics_Group();
	void setColor_Group( sf::Color color );	
	
	
	// In action.
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setColor( sf::Color color );
};