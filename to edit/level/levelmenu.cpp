#include "level/levelmenu.h"

Level_menu::Level_menu()
{
	state = new State;
	background = new MySprite;
	music = new Music;
	backtomenu = new Backtomenu( "", false );
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
}

void Level_menu::set( State* state )
{
	this->state = state;
	state->state = 0;
	
	// Set chunks
	if( !state->cSwitch )
	{
		backtomenu->turn();
	}
	
	// Set music volume
	music->setVolume( state->mVolume );
	
	// Set chunk volume
	backtomenu->setVolume( state->cVolume );
}
	
void Level_menu::load( int screen_w, int screen_h )
{
	background->load( "data/sprites/menu/background.png" );
	music->load( "data/music/Rayman Legends OST - Mysterious Swamps .mp3" );
	backtomenu->load( screen_w );
}


void Level_menu::handle( sf::Event &event )
{
	backtomenu->handle( event );
}

void Level_menu::draw( sf::RenderWindow* &window )
{
	if( state->mSwitch )
		music->play();
	
	window->draw( background->get() );

	backtomenu->draw( *window );
	
	if( backtomenu->getState() == 0 )
	{
		background->fadein( 3, 255 );
		music->fadein( 1, state->mVolume );
		backtomenu->fadein( 3, 255 );
	}
	else if( backtomenu->getState() == 1 )
	{
		background->fadeout( 3 );
		music->fadeout( 3 );
		backtomenu->fadeout( 3, 0 );
		
		if( background->getAlpha() == 0 )
		{
			music->halt();
			state->state = 2;
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