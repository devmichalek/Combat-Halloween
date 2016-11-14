#include "halloween/play_halloween.h"

Play_halloween::Play_halloween()
{
	state = new State;
	hero = new Hero;
	bg = new MySprite();
}

Play_halloween::~Play_halloween()
{
	free();
}

void Play_halloween::free()
{
	delete state;
	delete hero;
	delete bg;
}

	
void Play_halloween::load( int screen_w, int screen_h )
{
	bg->setName( "play_desert-bg" );
	bg->load( "data/sprites/play/0.png" );
	//...
}

void Play_halloween::setHero( int screen_w, int screen_h, int type )
{
	if( type == 0 )
	{
		hero->load( screen_w, screen_h, "data/sprites/hero/0/" );
	}
	else
	{
		hero->load( screen_w, screen_h, "data/sprites/hero/1/" );
	}
}


void Play_halloween::handle( sf::Event &event )
{
	// hero->handle( event );
}

void Play_halloween::draw( sf::RenderWindow* &window )
{
	window->draw( bg->get() );
	hero->draw( window );
	
	bg->fadein( 2 );
	hero->fadein( 2 );
	
	if( hero->attack() || hero->jump() ) {}
	else if( hero->moveLeft() ) {}
	else if( hero->moveRight() ) {}
	else hero->idle();
}

	
State* Play_halloween::getState()
{
	return state;
}

void Play_halloween::set( State* state )
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

	
bool Play_halloween::isQuit()
{
	if( state->state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Play_halloween::nextState()
{
	if( state->state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Play_halloween::backToLevel()
{
	if( state->state == 2 )
	{
		state->state = 0;
		// backtomenu->setState( 0 );
		return true;
	}
		
	return false;
}

	
void Play_halloween::reloadMusic()
{
	// music->reload();
}

