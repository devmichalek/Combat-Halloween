#pragma once

#include <string>

using namespace std;

class Skill
{
	int x, y;
	string name;
	string level;
	
	int line;
	int counter;
	
	int capacity;
	int capacity_line;
	
public:
	
	Skill();
	~Skill();
	void free();
	void reset();
	
	void setPosition( int x, int y );
	void setName( string name );
	void setLevel( string level );
	void setLine( int line );
	void setCapacity( int capacity );
	
	int getX();
	int getY();
	string getName();
	string getLevel();
	float getPercent();
	
	void mechanics();
	bool isAble();
};