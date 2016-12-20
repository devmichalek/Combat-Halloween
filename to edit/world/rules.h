#pragma once

#include "world/law.h"
#include <vector>

using namespace std;

class Rules
{
	vector < vector <Law*> > rules_right;
	vector < vector <Law*> > rules_left;
	vector < vector <Law*> > rules_bot;
	vector < vector <Law*> > rules_top;
	
public:
	Rules();
	~Rules();
	void free();
	
	void ruleRightSide();
	void ruleLeftSide();
	void ruleBotSide();
	void ruleTopSide( int number );
	
	vector <Law*> getRightRules( int which );
};