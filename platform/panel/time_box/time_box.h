#pragma once

#include <string>

using namespace std;

class Time_box
{
	int FPS;
	int counter;
	
	int sec;
	int min;
	int hour;
	
public:

	Time_box();
	~Time_box();
	void free();
	void reset();
	
	void load( int FPS );
	
	void mechanics();
	string getTimePlayed();
};