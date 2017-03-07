/**
    panel_menu.h
    Purpose: class Panel_menu as a main class in panel state.

    @author Adrian Michalek
    @version 2017.02.22
	@email adrmic98@gmail.com
*/

#include "panel_menu.h"


Panel_menu::Panel_menu()
{
	state = 0;
	
	bg = new MySprite;
	replay_button = new Replay_button;
	backtomenu_panel = new Backtomenu_panel;
}

Panel_menu::~Panel_menu()
{
	free();
}

void Panel_menu::free()
{
	sound.free();
	delete bg;
	delete replay_button;
	delete backtomenu_panel;
}

void Panel_menu::reset()
{
	replay_button->setState( 0 );
	backtomenu_panel->setState( 0 );
}



void Panel_menu::load( int screen_w, int screen_h )
{
	bg->setName( "panel_menu-background" );
	bg->load( "data/02_menu/background.png" );
	
	replay_button->load( screen_w, screen_h/2 );
	
	backtomenu_panel->load( screen_w, replay_button->getBot() +10 );
}

void Panel_menu::handle( sf::Event &event )
{
	if( backtomenu_panel->getState() != 2 )
	{
		replay_button->handle( event );
	}
	
	if( replay_button->getState() != 2 )
	{
		backtomenu_panel->handle( event );
	}
}

void Panel_menu::draw( sf::RenderWindow* &window )
{
	window->draw( bg->get() );
	replay_button->draw( window );
	backtomenu_panel->draw( window );
	
	
	if( replay_button->getState() == 2 || backtomenu_panel->getState() == 2 )
	{
		bg->fadeout( 4 );
		replay_button->fadeout( 4 );
		backtomenu_panel->fadeout( 4 );
	}
	else
	{
		bg->fadein( 3 );
		replay_button->fadein( 3 );
		backtomenu_panel->fadein( 3 );
	}
}



int Panel_menu::getState()
{
	return state;
}

void Panel_menu::setState( int state )
{
	this->state = state;
}



bool Panel_menu::backToMenu()
{
	return backtomenu_panel->nextState();
}

bool Panel_menu::backToPlatform()
{
	return replay_button->nextState();
}
