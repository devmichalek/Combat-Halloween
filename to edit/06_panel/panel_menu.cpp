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
	
	music = new Music;
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
	
	delete music;
	
	if( bg != NULL )
		delete bg;
		
	if( replay_button != NULL )
		delete replay_button;
	
	if( backtomenu_panel != NULL )
		delete backtomenu_panel;
}

void Panel_menu::reset()
{
	music->halt();
	replay_button->setState( 0 );
	backtomenu_panel->setState( 0 );
}



void Panel_menu::load( int screen_w, int screen_h )
{
	bg->setName( "panel_menu-background" );
	bg->load( "data/02_menu/background.png" );
	
	replay_button->load( screen_w, screen_h/2 );
	
	backtomenu_panel->load( screen_w, replay_button->getBot() +10 );
	
	music->setID( "panel_menu-music" );
	music->load( "data/06_panel/music.mp3", 50 );
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
	if( sound.getMusicPlay() )
	{
		music->play();
	}
	
	window->draw( bg->get() );
	replay_button->draw( window );
	backtomenu_panel->draw( window );
	
	
	if( replay_button->getState() == 2 || backtomenu_panel->getState() == 2 )
	{
		sf::Uint8 value = 4;
		music->fadeout( 1, 0 );
		bg->fadeout( value );
		replay_button->fadeout( value );
		backtomenu_panel->fadeout( value );
	}
	else
	{
		sf::Uint8 value = 3;
		music->fadein( 1, sound.getMusicVolume() );
		bg->fadein( value );
		replay_button->fadein(value );
		backtomenu_panel->fadein( value );
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



void Panel_menu::setSound()
{
	// Set chunks
	if( !sound.getChunkPlay() )
	{
		replay_button->turnOff();
		backtomenu_panel->turnOff();
	}
	else
	{
		replay_button->turnOn();
		backtomenu_panel->turnOn();
		
		// Set chunk volume
		replay_button->setVolume( sound.getChunkVolume() );
		backtomenu_panel->setVolume( sound.getChunkVolume() );
	}
	
	// Set music volume
	music->setVolume( sound.getMusicVolume() );
}

void Panel_menu::reloadMusic()
{
	music->reload();
	Mix_HaltMusic();
}