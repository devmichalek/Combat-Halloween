#pragma once

#include <vector>
#include <cstdint>
#include <string>

using namespace std;

class Rules
{
	vector < vector <int8_t> > rules_right;
	
public:
	Rules();
	~Rules();
	void free();
	
	void rule();
	
	vector <int8_t> getRightRules( int which );
	
	int getTopBlockFor( int nr );
	int getBotBlockFor( int nr );
	
	int fillForTop( int nr, int need );
	int fillForBot( int nr );
	
	unsigned getSize( int which );
	int8_t getBlock( int which );
};