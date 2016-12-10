#include "winter/play_winter.h"

Play_winter::Play_winter()
{
	state = new State;
	hero = new Hero;
	bg = new MySprite;
	random_block = new Random_block;
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
	delete random_block;
}

	
void Play_winter::load( int screen_w, int screen_h )
{
	bg->setName( "play_winter-bg" );
	bg->load( "data/sprites/play/2.png" );
	random_block->load( screen_w, screen_h, 2 );
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
	bg->fadein( 2 );
	hero->fadein( 2 );
	
	window->draw( bg->get() );
	
	random_block->drawBG( window );
	hero->draw( window );
	random_block->draw( window );
	
	// Y
	hero->gravitation();
	if( random_block->checkCollision( hero->getX(), hero->getY(), hero->getW(), hero->getH() ) )
	{
		hero->weightlessness();
	}
	else
	{
		hero->gliding();
	}
	

	// X
	hero->sliding();
	if( hero->jumpAttack() )
	{
		if( random_block->checkCollision( hero->getX(), hero->getY(), hero->getW(), hero->getH() ) ||
			hero->getX() + hero->getW()> random_block->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	else if( hero->attack() ) {}
	else if( hero->jump() )
	{
		if( random_block->checkCollision( hero->getX(), hero->getY(), hero->getW(), hero->getH() ) ||
			hero->getX() + hero->getW()> random_block->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	else if( hero->move() )
	{
		if( random_block->checkCollision( hero->getX(), hero->getY(), hero->getW(), hero->getH() ) ||
			hero->getX() + hero->getW()> random_block->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoMove();
		}
	}
	else
	{
		hero->idle();
	}
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

