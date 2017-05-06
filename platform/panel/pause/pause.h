#pragma once

#include "drawable/text.h"
#include "drawable/sprite.h"
#include <vector>

class Pause
{
	MyText text;
	MySprite sprite;
	
	// info
	vector <MyText*> info;
	vector <MyText*> info_a;
	
	bool focus;
	bool paused;
	bool allowed;
	
	// For quit
	int c;
	int t;
	bool dead;
	
public:
	
	Pause();
	~Pause();
	void free();
	void reset();
	
	void load( unsigned screen_w, unsigned screen_h, int FPS );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadeout( int j = 1, int min = 0 );
	
	// Other.
	bool isPaused();
	void allow();
	string getName( int n );
	bool isDead();
};