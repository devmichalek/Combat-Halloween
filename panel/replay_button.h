/**
    replay_button.h
    Purpose: class Replay_button as a simple button with label 'replay'.

    @author Adrian Michalek
    @version 2017.02.01
	@email adrmic98@gmail.com
*/

#pragma once

#include "backtomenu_panel.h"

class Replay_button :public Backtomenu_panel
{
	
public:
	
	void load( float x );
	
	int getRight();
	int getTop();
};