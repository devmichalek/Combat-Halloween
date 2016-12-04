#pragma once


class Activity
{
	
public:
	int line;
	int counter;
	bool active;
	
	Activity();
	~Activity();
	void free();
	void summarize();
};