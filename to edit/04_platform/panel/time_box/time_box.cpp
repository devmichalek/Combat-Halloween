#include "time_box.h"
#include "file/file.h"

Time_box::Time_box()
{
	free();
}

Time_box::~Time_box()
{
	free();
}

void Time_box::free()
{
	FPS = 0;
	counter = 0;
	
	sec = min = hour = 0;
}

void Time_box::reset()
{
	counter = 0;
	
	sec = min = hour = 0;
}



void Time_box::load( int FPS )
{
	free();
	
	this->FPS = FPS;
}



void Time_box::mechanics()
{
	counter ++;
	if( counter == FPS )
	{
		sec ++;
		counter = 0;
	}
	
	if( sec == 60 )
	{
		min ++;
		sec = 0;
	}
	
	if( min == 60 )
	{
		hour ++;
		min = 0;
	}
}

string Time_box::getTimePlayed()
{
	string result = "";
	
	if( sec != 0 )
	{
		result += " " +con::itos( sec ) +"s";
	}
	
	if( min != 0 )
	{
		result += " " +con::itos( min ) +"m";
	}
	
	if( hour != 0 )
	{
		result += con::itos( hour ) +"h";
	}
	
	return result;
}
