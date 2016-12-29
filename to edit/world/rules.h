#pragma once

#include "world/law.h"
#include <vector>

using namespace std;

class Rules
{
	vector < vector <Law*> > rules_right;
	vector < vector <Law*> > rules_left;
	vector < vector <Law*> > rules_bot;
	// vector < vector <Law*> > rules_top;
	
public:
	Rules();
	~Rules();
	void free();
	
	void ruleRightSide();
	void ruleLeftSide();
	void ruleBotSide();
	// void ruleTopSide();
	
	vector <Law*> getRightRules( int which );
	int getTopBlockFor( int nr );
	int getBotBlockFor( int nr );
	int fillForTop( int nr, int need );
	int fillForBot( int nr );
};