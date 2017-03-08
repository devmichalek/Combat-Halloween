#pragma once

#include "showdamage.h"

class Showheal :public Showdamage
{
	int x, y;
	vector <float> vels;
	vector <float> lines;
	vector <int> alphas;
	vector <float> distances;
	vector <string> texts;
	
	MyText text;
	
public:
	
	using Showdamage::Showdamage;

    void load();
	void run( string dmg );
};