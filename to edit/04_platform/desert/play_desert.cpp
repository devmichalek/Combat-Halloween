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
	greenery = new Greenery;
	ladder = new Ladder;
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
	delete greenery;
	delete ladder;
}

	
void Play_desert::load( int screen_w, int screen_h )
{
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	bg->load( "data/sprites/play/3.png", screen_w, screen_h );
	brick->load( screen_w, screen_h, 3 );
	kunai->load();
	heart->load();
	greenery->load( 3 );
	ladder->load( 3 );
}

void Play_desert::setHero( int screen_w, int screen_h, int type )
{
	hero->load( screen_w, screen_h, "data/sprites/hero/" + to_string( type ) + "/" );
	bg->setXY( hero->getX(), hero->getY() );
}

void Play_desert::setWorldsize( int size )
{
	brick->createTopBorders( size, ladder->getW( 0 ), ladder->getH( 0 ) );
	brick->createLeftBorders();
	brick->createRightBorders();
	brick->setLeft();
	brick->setRight();
	brick->createStuffing( 10, 11 );
	brick->createStuffing( 14, 11 );
	brick->createStuffing( 8, 15 );
	brick->createTopIslands( ladder->getW( 1 ), ladder->getH( 1 ) );
	brick->createBotIslands( ladder->getW( 1 ), ladder->getH( 1 ) );
	
	ladder->positioning( brick->getPlanks() );
	greenery->positioning( brick->getBlocks() );
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
	greenery->fadein( 2 );
	ladder->fadein( 2 );

	
	bg->draw( window );
	greenery->drawBG( window, screen_w );
	ladder->draw( window, screen_w );
	hero->draw( window );
	kunai->draw( window );
	brick->draw( window );
	greenery->draw( window, screen_w );
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

