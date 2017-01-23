#pragma once

#include <vector>
#include <cstdint>

using namespace std;

class Rules
{
	vector < vector <int8_t> > rules_right;
	
public:
	Rules();
	~Rules();
	void free();
	
	void ruleRightSide();
	
	vector <int8_t> getRightRules( int which );
	
	int getTopBlockFor( int nr );
	int getBotBlockFor( int nr );
	
	int fillForTop( int nr, int need );
	int fillForBot( int nr );
};