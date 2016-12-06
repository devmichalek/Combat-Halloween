#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "menu/click.h"

class Choice :public Click
{
	MySprite button;
	MyText text;
	
	sf::Uint8 nr;		// number of worlds
	MySprite* world;
	
	MySprite frame;
	
	MyText information;
	
	
	int counter; 	// random
	int result;		// ended result
	int chosen;		// if user moved on the one of images
	
	// To move - animation
	int range;
	
public:
	
	Choice();
	~Choice();

	void load( int screen_w, int screen_h );
	void handle( sf::Event &event );
	void draw( sf::RenderWindow &window );
	
	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
	
	int getResult();
	sf::Uint8 getAlpha();
	bool isChosen();
	
	void reset();
	
	bool move( int vel, int ran );	// move horizontal
};