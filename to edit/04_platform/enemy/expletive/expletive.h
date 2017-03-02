#pragma once

#include <vector>
#include "04_platform/enemy/expletive/slab.h"

using namespace std;

class Expletive
{
	vector <Slab*> hits;
	vector <Slab*> attacks;
	
public:
	
	Expletive();
	~Expletive();
	void free();
	int strToInt( string s );
	
	void load( string name );
	void playHits();
	void playAttacks();
};