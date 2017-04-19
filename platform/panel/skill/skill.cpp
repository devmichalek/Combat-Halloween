/**
    skill.h
    Purpose: class Skill as a piece with position, own name, own level etc.

    @author Adrian Michalek
    @version 2016.03.06
	@email adrmic98@gmail.com
*/

#include "skill.h"

Skill::Skill()
{
	free();
}

Skill::~Skill()
{
	free();
}

void Skill::free()
{
	x = y = 0;
	name = "";
	level = "";
}

void Skill::reset()
{
	counter = 0;
}



void Skill::setPosition( int x, int y )
{
	this->x = x;
	this->y = y;
}

void Skill::setName( string name )
{
	this->name = name;
}

void Skill::setLevel( string level )
{
	this->level = level;
}

void Skill::setLine( int line )
{
	counter = 0;
	this->line = line;
}




int Skill::getX()
{
	return x;
}

int Skill::getY()
{
	return y;
}

string Skill::getName()
{
	return name;
}

string Skill::getLevel()
{
	return level;
}

float Skill::getPercent( int h )
{
	float percent = static_cast <float> (counter *100 /line );
	// printf( "%f %d %d\n", percent, counter, line );
	return percent /100 *h;
}



void Skill::mechanics()
{
	if( counter > 1 )
	{
		counter ++;
	}
	
	if( counter == line )
	{
		counter = 0;
	}
}

bool Skill::isAble()
{
	if( counter == 0 )
	{
		counter = 1;
		return true;
	}
	
	return false;
}

void Skill::used()
{
	if( counter == 1 )
	{
		counter = 2;
	}
}