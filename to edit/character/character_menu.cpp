#include "character/character_menu.h"


Character_menu::Character_menu()
{
	state = new State;
	character = new Character;
	bg = new MySprite;
	music = new Music;
	backtomenu = new Backtomenu( "", false );
}

Character_menu::~Character_menu()
{
	free();
}

void Character_menu::free()
{
	delete state;
	delete character;
	delete bg;
	delete music;
	delete backtomenu;
}

void Character_menu::load( int screen_w, int screen_h )
{
	bg->load( "data/sprites/menu/background.png" );
	music->load( "data/music/Rayman Legends OST - The Fortified Castle.mp3" );
	backtomenu->load( screen_w );
	character->load( screen_w, screen_h );
}

void Character_menu::handle( sf::Event &event )
{
	if( !character->nextState() )
	{
		backtomenu->handle( event );
		character->handle( event );
	}
}

void Character_menu::draw( sf::RenderWindow* &window )
{
	if( state->mSwitch && state->state == 0 )
		music->play();
		
	window->draw( bg->get() );
	backtomenu->draw( *window );
	character->draw( window );
	
	if( backtomenu->getState() == 0 && !character->nextState() )
	{
		bg->fadein( 3, 255 );
		music->fadein( 1, state->mVolume );
		backtomenu->fadein( 3, 255 );
		character->fadein( 3, 255 );
	}
	else if( backtomenu->getState() == 1 && !character->nextState() )
	{
		bg->fadeout( 3 );
		music->fadeout( 3 );
		backtomenu->fadeout( 3, 0 );
		character->fadeout( 3, 0 );
		
		if( character->getAlpha() == 0 )
		{
			music->halt();
			backtomenu->setState( 0 );
			state->state = 2;
		}
	}
	else if( character->nextState() )
	{
		bg->fadeout( 3 );
		music->fadeout( 3 );
		backtomenu->fadeout( 3, 0 );
		character->fadeout( 3, 0 );
		
		if( character->getAlpha() == 0 )
		{
			music->halt();
			state->state = 1;
		}
	}
}

State* Character_menu::getState()
{
	return state;
}
	
void Character_menu::set( State* state )
{
	this->state = state;
	state->state = 0;
	
	// Set chunks
	if( !state->cSwitch )
	{
		backtomenu->turn();
		character->turn();
	}
	
	// Set music volume
	music->setVolume( state->mVolume );
	
	// Set chunk volume
	backtomenu->setVolume( state->cVolume );
	character->setVolume( state->cVolume );
}
	
	
	
	
bool Character_menu::isQuit()
{
	if( state->state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Character_menu::nextState()
{
	if( state->state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Character_menu::backToMenu()
{
	if( state->state == 2 )
	{
		state->state = 0;
		backtomenu->setState( 0 );
		return true;
	}
		
	return false;
}


void Character_menu::reloadMusic()
{
	music->reload();
}

int Character_menu::getCharacter()
{
	return character->getResult();
}