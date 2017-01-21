#include "play_desert.h"

Play_desert::Play_desert()
{
	state = 0;
	
	// Create play_desert stuff.
	sound = new Sound;
	hero = new Hero;
	bg = new Moving_bg;
	brick = new Brick;
	kunai = new Kunai;
	heart = new Heart;
	scope = new Scope;
	vegetation = new Vegetation;
}

Play_desert::~Play_desert()
{
	free();
}

void Play_desert::free()
{
	delete sound;
	delete hero;
	delete bg;
	delete brick;
	delete kunai;
	delete heart;
	delete scope;
	delete vegetation;
}

	
void Play_desert::load( int screen_w, int screen_h )
{
	bg->load( "data/sprites/play/3.png", screen_w, screen_h );
	brick->load( screen_w, screen_h, 16, 3 );
	kunai->load();
	heart->load();
}

void Play_desert::setHero( int screen_w, int screen_h, int type )
{
	hero->load( screen_w, screen_h, "data/sprites/hero/" + to_string( type ) + "/" );
	bg->setXY( hero->getX(), hero->getY() );
}

void Play_desert::setWorldsize( int size )
{
	brick->positioning( size );
	vegetation->load( 3 );
	vegetation->positioning( brick->getBlocks() );
}


void Play_desert::handle( sf::Event &event )
{
	// hero->handle( event );
}

void Play_desert::draw( sf::RenderWindow* &window )
{
	mechanics();
	
	bg->fadein( 2 );
	brick->fadein( 2 );
	hero->fadein( 2 );
	kunai->fadein( 2 );
	heart->fadein( 2 );
	vegetation->fadein( 2 );

	
	bg->draw( window );
	vegetation->drawBG( window, brick->getScreenWidth() );
	brick->drawLadders( window );
	hero->draw( window );
	kunai->draw( window );
	brick->draw( window );
	vegetation->draw( window, brick->getScreenWidth() );
	heart->draw( window );
}

	
int Play_desert::getState()
{
	return state;
}

void Play_desert::set( int state, Sound* sound )
{
	state = 0;
	
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

	
bool Play_desert::isQuit()
{
	if( state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Play_desert::nextState()
{
	if( state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Play_desert::backToLevel()
{
	if( state == 2 )
	{
		state = 0;
		return true;
	}
		
	return false;
}

	
void Play_desert::reloadMusic()
{
	// music->reload();
}

