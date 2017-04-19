/**
    damage.h
    Purpose: struct Damage counts damage for particular variable.

    @author Adrian Michalek
    @version 2017.03.03
	@email adrmic98@gmail.com
*/

#pragma once

#include <string>
using namespace std;

struct Damage
{
	string multiply( int which, float value, int number );
};