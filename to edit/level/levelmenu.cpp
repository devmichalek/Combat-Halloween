#include "level/levelmenu.h"

Level_menu::Level_menu()
{
	state = new State;
	background = new MySprite;
	music = new Music;
	backtomenu = new Backtomenu( "", false );
	choice = new Choice;
}

Level_menu::~Level_menu()
{
	free();
}

void Level_menu::free()
{
	delete background;
	delete music;
	delete backtomenu;
	delete choice;
}

void Level_menu::set( State* state )
{
	this->state = state;
	state->state = 0;
	
	// Set chunks
	if( !state->cSwitch )
	{
		backtomenu->turn();
		choice->turn();
	}
	
	// Set music volume
	music->setVolume( state->mVolume );
	
	// Set chunk volume
	backtomenu->setVolume( state->cVolume );
	choice->setVolume( state->cVolume );
}
	
void Level_menu::load( int screen_w, int screen_h )
{
	background->load( "data/sprites/menu/background.png" );
	music->load( "data/music/Rayman Legends OST - Mysterious Swamps .mp3" );
	backtomenu->load( screen_w );
	choice->load( screen_w, screen_h );
}


void Level_menu::handle( sf::Event &event )
{
	if( !choice->isReady() )
	{
		backtomenu->handle( event );
		choice->handle( event );
	}
}

void Level_menu::draw( sf::RenderWindow* &window )
{
	if( state->mSwitch && state->state == 0 )
		music->play();
	
	window->draw( background->get() );
	backtomenu->draw( *window );
	choice->draw( *window );
	
	if( backtomenu->getState() == 0 && !choice->isReady() )
	{
		background->fadein( 3, 255 );
		music->fadein( 1, state->mVolume );
		backtomenu->fadein( 3, 255 );
		choice->fadein( 3, 255 );
	}
	else if( backtomenu->getState() == 1 && !choice->isReady() )
	{
		background->fadeout( 3 );
		music->fadeout( 3 );
		backtomenu->fadeout( 3, 0 );
		choice->fadeout( 3, 0 );
		
		if( background->getAlpha() == 0 )
		{
			music->halt();
			backtomenu->setState( 0 );
			state->state = 2;
		}
	}
	else if( choice->isReady() )
	{
		background->fadeout( 3 );
		music->fadeout( 3 );
		backtomenu->fadeout( 3, 0 );
		choice->fadeout( 3, 0 );
		
		if( background->getAlpha() == 0 )
		{
			music->halt();
			state->state = 1;
		}
	}
}

	
bool Level_menu::isQuit()
{
	if( state->state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Level_menu::nextState()
{
	if( state->state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Level_menu::backToMenu()
{
	if( state->state == 2 )
	{
		state->state = 0;
		backtomenu->setState( 0 );
		return true;
	}
		
	return false;
}


void Level_menu::reloadMusic()
{
	music->reload();
}