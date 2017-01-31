#include "04_platform/winter/play_winter.h"

Play_winter::Play_winter()
{
	state = 0;
	
	// Create Play_winter objects
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

Play_winter::~Play_winter()
{
	free();
}



void Play_winter::free()
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

void Play_winter::reset()
{
	hero->reset( screen_h );
	bg->setXY( hero->getX(), hero->getY() );
	int distance = brick->reset();
	greenery->reset( distance );
	ladder->reset( distance );
	heart->reset();
	scope->reset();
}



void Play_winter::load( int screen_w, int screen_h )
{
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	bg->load( "data/sprites/play/2.png", screen_w, screen_h );
	brick->load( screen_w, screen_h, 2 );
	kunai->load();
	heart->load();
	greenery->load( 2 );
	ladder->load( 2 );
}

void Play_winter::handle( sf::Event &event )
{
	//...
}

void Play_winter::draw( sf::RenderWindow* &window )
{
	mechanics();
	
	if( hero->isDead() )
	{
		sf::Uint8 v = 1;
		bg->fadeout( v );
		brick->fadeout( v );
		hero->fadeout( v );
		kunai->fadeout( v );
		heart->fadeout( v );
		greenery->fadeout( v );
		ladder->fadeout( v );
	}
	else
	{
		sf::Uint8 v = 2;
		bg->fadein( v );
		brick->fadein( v );
		hero->fadein( v );
		kunai->fadein( v );
		heart->fadein( v );
		greenery->fadein( v );
		ladder->fadein( v );
	}
	

	
	bg->draw( window );
	greenery->drawBG( window, screen_w );
	ladder->draw( window, screen_w );
	hero->draw( window );
	kunai->draw( window );
	brick->draw( window );
	greenery->draw( window, screen_w );
	heart->draw( window );
}



void Play_winter::setHero( int screen_w, int screen_h, int type )
{
	hero->load( screen_w, screen_h, "data/sprites/hero/" + to_string( type ) + "/" );
	
	bg->setXY( hero->getX(), hero->getY() );
}

void Play_winter::setWorldsize( int size )
{
	brick->reserve( size );
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
	brick->createWater();
	brick->shrink();
	
	ladder->positioning( brick->getPlanks() );
	greenery->positioning( brick->getBlocks() );
}



Sound* Play_winter::getSound()
{
	return sound;
}

int Play_winter::getState()
{
	return state;
}

void Play_winter::set( int state, Sound* sound )
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



bool Play_winter::nextState()
{
	if( hero->isDead() && bg->getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

bool Play_winter::backToLevel()
{
	return false;
}