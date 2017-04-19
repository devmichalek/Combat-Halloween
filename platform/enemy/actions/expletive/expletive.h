#pragma once

#include <vector>
#include "slab.h"

using namespace std;

class Expletive
{
	vector <Slab*> hits;
	vector <Slab*> attacks;
	
public:
	
	Expletive();
	~Expletive();
	void free();
	
	void load( string name );
	void playHits();
	void playAttacks();
	
	// Sound stuff.
	void turn();
	void turnOn();
	void turnOff();
	void setVolume( int v );
};