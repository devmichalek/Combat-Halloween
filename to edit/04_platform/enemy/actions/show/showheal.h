#pragma once

#include "showdamage.h"

class Showheal :public Showdamage
{
	
public:
	
	using Showdamage::Showdamage;

    void load();
	void run( int dmg );
};