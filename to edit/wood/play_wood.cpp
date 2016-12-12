#include "wood/play_wood.h"

Play_wood::Play_wood()
{
	state = new State;
	hero = new Hero;
	bg = new Moving_bg;
	random_block = new Random_block;
	kunai = new Kunai;
	heart = new Heart;
	golem = new Golem;
}

Play_wood::~Play_wood()
{
	free();
}

void Play_wood::free()
{
	delete state;
	delete hero;
	delete bg;
	delete random_block;
	delete kunai;
	delete heart;
	delete golem;
}

	
void Play_wood::load( int screen_w, int screen_h )
{
	bg->load( "data/sprites/play/1.png" );
	random_block->load( screen_w, screen_h, 1 );
	kunai->load();
	heart->load();
	golem->load();
	golem->setXY( 400, screen_h -128 );
}

void Play_wood::setHero( int screen_w, int screen_h, int type )
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


void Play_wood::handle( sf::Event &event )
{
	// hero->handle( event );
}

void Play_wood::draw( sf::RenderWindow* &window )
{
	mechanics();
	
	bg->fadein( 2 );
	random_block->fadein( 2 );
	hero->fadein( 2 );
	kunai->fadein( 2 );
	heart->fadein( 2 );
	golem->fadein( 2 );
	
	bg->draw( window );
	random_block->drawBG( window );
	hero->draw( window );
	kunai->draw( window );
	golem->draw( window );
	random_block->draw( window );
	heart->draw( window );
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

