#pragma once

#include "drawable/sprite.h"
#include <vector>

using namespace std;

class Day
{
	enum
	{
		I = 20,
		S = 20,
		N = 25
	};
	
	bool change;
	bool count;
	
	sf::Uint8 state;
	sf::Uint8 counter;
	sf::Uint8 sec;
	sf::Uint8 line;
	
	sf::Uint8 r, g, b, a;
	vector <sf::Color> colors;
	
	MySprite overlay;
	
public:

	Day();
	~Day();
	void free();
	void reset( Rect* rect );
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void setInTime();
	void mechanics();
};