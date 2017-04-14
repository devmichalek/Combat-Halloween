/**
    backtomenu_panel.h
    Purpose: class Backtomenu_panel as a simple button with label 'menu'.

    @author Adrian Michalek
    @version 2017.02.27
	@email adrmic98@gmail.com
*/

#pragma once

#include "02_menu/play_button/play_button.h"

class Backtomenu_panel :public Play_button
{
	
public:
	
	void load( int r, int t );
};