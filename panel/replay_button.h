/**
    replay_button.h
    Purpose: class Replay_button as a simple button with label 'replay'.

    @author Adrian Michalek
    @version 2017.02.01
	@email adrmic98@gmail.com
*/

#pragma once

#include "menu/play_button/play_button.h"

class Replay_button :public Play_button
{
	
public:
	
	void load( int bot );
	
	int getRight();
	int getTop();
};