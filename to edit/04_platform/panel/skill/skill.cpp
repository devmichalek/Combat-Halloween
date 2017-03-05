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
	capacity = capacity_line;
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

void Skill::setCapacity( int capacity )
{
	this->capacity = capacity;
	this->capacity_line = capacity;
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

float Skill::getPercent()
{
	return static_cast <float> (counter) *100 /line;
}



void Skill::mechanics()
{
	if( counter > 0 )
	{
		counter ++;
	}
	
	if( counter == line )
	{
		counter = 0;
		
		if( capacity < capacity_line )
		{
			capacity ++;
		}
	}
}

bool Skill::isAble()
{
	if( capacity > 0 && counter == 0 )
	{
		capacity --;
		counter = 1;
		return true;
	}
	
	return false;
}