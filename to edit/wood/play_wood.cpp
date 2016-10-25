#include "wood/play_wood.h"

Play_wood::Play_wood()
{
	state = new State;
	hero = new Hero;
}

Play_wood::~Play_wood()
{
	free();
}

void Play_wood::free()
{
	delete state;
	delete hero;
}

	
void Play_wood::load( int screen_w, int screen_h )
{
	hero->load( screen_w, screen_h );
	//...
}


void Play_wood::handle( sf::Event &event )
{
	hero->handle( event );
}

void Play_wood::draw( sf::RenderWindow* &window )
{
	hero->draw( window );
	
	hero->fadein( 2 );
}

	
State* Play_wood::getState()
{
	return state;
}

void Play_wood::set( State* state )
{
	this->state = state;
	state->state = 0;
	
	/*
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
	*/
}

	
bool Play_wood::isQuit()
{
	if( state->state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Play_wood::nextState()
{
	if( state->state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Play_wood::backToLevel()
{
	if( state->state == 2 )
	{
		state->state = 0;
		// backtomenu->setState( 0 );
		return true;
	}
		
	return false;
}

	
void Play_wood::reloadMusic()
{
	// music->reload();
}

