/**
    skill.h
    Purpose: class Skill as a piece with position, own name, own level etc.

    @author Adrian Michalek
    @version 2016.03.06
	@email adrmic98@gmail.com
*/

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
	
public:
	
	Skill();
	~Skill();
	void free();
	void reset();
	
	void setPosition( int x, int y );
	void setName( string name );
	void setLevel( string level );
	void setLine( int line );
	
	int getX();
	int getY();
	string getName();
	string getLevel();
	float getPercent( int h );
	
	void mechanics();
	bool isAble();
	void used();
};