#pragma once

#include "law.h"
#include <vector>

using namespace std;

class Rules
{
	vector < vector <Law*> > rules_right;
	
public:
	Rules();
	~Rules();
	void free();
	
	void ruleRightSide();
	
	vector <Law*> getRightRules( int which );
	
	int getTopBlockFor( int nr );
	int getBotBlockFor( int nr );
	
	int fillForTop( int nr, int need );
	int fillForBot( int nr );
};