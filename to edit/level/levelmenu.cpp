#include "level/levelmenu.h"

Level_menu::Level_menu()
{
	state = new State;
	background = new MySprite;
	music = new Music;
	backtomenu = new Backtomenu( "", false );
	choice = new Choice;
	character = new Character;
	worldsize = new Worldsize;
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
	delete choice;
	delete character;
	delete worldsize;
}

State* Level_menu::getState()
{
	return state;
}

void Level_menu::set( State* state )
{
	this->state = state;
	state->state = 0;
	
	// Set chunks
	if( !state->cSwitch )
	{
		if( backtomenu->isPlayable() )
		{
			backtomenu->turn();
			choice->turn();
			worldsize->turn();
		}
	}
	else
	{
		if( !backtomenu->isPlayable() )
		{
			backtomenu->turn();
			choice->turn();
			worldsize->turn();
		}
	}
	
	// Set music volume
	music->setVolume( state->mVolume );
	
	// Set chunk volume
	backtomenu->setVolume( state->cVolume );
	choice->setVolume( state->cVolume );
	worldsize->setVolume( state->cVolume );
}
	
void Level_menu::load( int screen_w, int screen_h )
{
	background->load( "data/sprites/menu/background.png" );
	music->load( "data/music/Rayman Legends OST - Mysterious Swamps .mp3" );
	backtomenu->load( screen_w );
	choice->load( screen_w, screen_h );
	character->load( screen_w, screen_h );
	worldsize->load( screen_w, screen_h );
}


void Level_menu::handle( sf::Event &event )
{
	if( !choice->isChosen() && backtomenu->getState() == 0 )
	{
		choice->handle( event );
		worldsize->handle( event );
		backtomenu->handle( event );
	}
	else if( !character->nextState() )
	{
		if( backtomenu->getState() == 1 )
		{
			character->handle( event );
			backtomenu->handle( event );
		}
	}
}

void Level_menu::draw( sf::RenderWindow* &window )
{
	if( state->mSwitch && state->state == 0 )
		music->play();
	
	if( backtomenu->getState() == 0 )
	if( choice->isChosen() )
	{
		character->move( -20, 0 );
		worldsize->move( -20, -1000 );
		if( choice->move( -20, -1000 ) )
			backtomenu->setState( 1 );
	}
	
	window->draw( background->get() );
	backtomenu->draw( *window );
	choice->draw( *window );
	worldsize->draw( *window );
	character->draw( window );
	
	if( backtomenu->getState() == 0 )
	{
		background->fadein( 3, 255 );
		music->fadein( 1, state->mVolume );
		backtomenu->fadein( 3, 255 );
		choice->fadein( 3, 255 );
		worldsize->fadein( 3, 255 );
		character->fadein( 3, 255 );
	}
	
	else if( backtomenu->getState() == -1 )
	{
		background->fadeout( 3 );
		music->fadeout( 3 );
		backtomenu->fadeout( 3, 0 );
		choice->fadeout( 3, 0 );
		worldsize->fadeout( 3, 0 );
		character->fadeout( 3, 0 );
		
		if( choice->getAlpha() == 0 )
		{
			music->halt();
			backtomenu->setState( 0 );
			state->state = 2;
		}
	}
	
	else if( backtomenu->getState() == 1 )
	{
		if( character->nextState() )
		{
			background->fadeout( 3 );
			music->fadeout( 3 );
			backtomenu->fadeout( 3, 0 );
			choice->fadeout( 3, 0 );
			worldsize->fadeout( 3, 0 );
			character->fadeout( 3, 0 );
			
			if( choice->getAlpha() == 0 )
			{
				music->halt();
				backtomenu->setState( 0 );
				state->state = 1;
			}
		}
	}
	
	else if( backtomenu->getState() == 2 )
	{
		character->move( 20, 1000 );
		worldsize->move( 20, 0 );
		if( choice->move( 20, 0 ) )
		{
			choice->reset();
			backtomenu->setState( 0 );
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
		worldsize->reset();
		return true;
	}
		
	return false;
}


void Level_menu::reloadMusic()
{
	music->reload();
}

int Level_menu::getMap()
{
	return choice->getResult();
}

int Level_menu::getCharacter()
{
	return character->getResult();
}

int Level_menu::getWorldsize()
{
	return worldsize->getResult();
}