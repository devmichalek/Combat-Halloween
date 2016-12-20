#include "winter/play_winter.h"

Play_winter::Play_winter()
{
	state = new State;
	hero = new Hero;
	bg = new MySprite;
	brick = new Brick;
	kunai = new Kunai;
	heart = new Heart;
	golem = new Golem;
}

Play_winter::~Play_winter()
{
	free();
}

void Play_winter::free()
{
	delete state;
	delete hero;
	delete bg;
	delete brick;
	delete kunai;
	delete heart;
	delete golem;
}

	
void Play_winter::load( int screen_w, int screen_h )
{
	bg->setName( "play_winter-bg" );
	bg->load( "data/sprites/play/2.png" );
	brick->load( screen_w, screen_h, 18, 2 );
	kunai->load();
	heart->load();
	golem->load();
	golem->setXY( 400, screen_h -128 );
}

void Play_winter::setHero( int screen_w, int screen_h, int type )
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


void Play_winter::handle( sf::Event &event )
{
	// hero->handle( event );
}

void Play_winter::draw( sf::RenderWindow* &window )
{
	mechanics();
	
	bg->fadein( 2 );
	brick->fadein( 2 );
	hero->fadein( 2 );
	kunai->fadein( 2 );
	heart->fadein( 2 );
	golem->fadein( 2 );
	
	window->draw( bg->get() );
	brick->drawLadders( window );
	hero->draw( window );
	kunai->draw( window );
	golem->draw( window );
	brick->draw( window );
	heart->draw( window );
}

	
State* Play_winter::getState()
{
	return state;
}

void Play_winter::set( State* state )
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

	
bool Play_winter::isQuit()
{
	if( state->state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Play_winter::nextState()
{
	if( state->state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Play_winter::backToLevel()
{
	if( state->state == 2 )
	{
		state->state = 0;
		// backtomenu->setState( 0 );
		return true;
	}
		
	return false;
}

	
void Play_winter::reloadMusic()
{
	// music->reload();
}

