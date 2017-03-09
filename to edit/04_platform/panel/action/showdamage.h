#pragma once

#include "drawable/text.h"
#include <vector>

class Showdamage
{
protected:
	
	int x, y;
	vector <float> vels;
	vector <float> lines;
	vector <int> alphas;
	vector <float> distances;
	vector <string> texts;
	
	MyText text;
	
public:
	
	Showdamage();
    ~Showdamage();
	void free();
	void reset();

    void load();
    void draw( sf::RenderWindow &window );
	
	void run( string dmg );
	void focus( int x, int y );
	void fadeout( int i = 1, int min = 0 );
};