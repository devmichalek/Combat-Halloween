#include "levelmenu.h"

Level_menu::Level_menu()
{
	state = 0;
	
	// Create level menu objects
	sound = new Sound;
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
	delete sound;
	delete background;
	delete music;
	delete backtomenu;
	delete choice;
	delete character;
	delete worldsize;
}



int Level_menu::getState()
{
	return state;
}

void Level_menu::set( int state, Sound* sound )
{
	state = 0;
	this->sound = sound;
	
	// Set chunks
	if( sound->getChunkPlay() != backtomenu->isPlayable() )
	{
		backtomenu->turn();
		choice->turn();
		worldsize->turn();
	}
	
	// Set music volume
	music->setVolume( sound->getMusicVolume() );
	
	// Set chunk volume
	backtomenu->setVolume( sound->getChunkVolume() );
	choice->setVolume( sound->getChunkVolume() );
	character->setVolume( sound->getChunkVolume() );
	worldsize->setVolume( sound->getChunkVolume() );
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
	if( sound->getMusicPlay() && state == 0 )
	{
		music->play();
	}
		
	
	if( backtomenu->getState() == 0 )
	{
		if( choice->isChosen() )
		{
			character->move( -20, 0 );
			worldsize->move( -20, -1000 );
			if( choice->move( -20, -1000 ) )
			{
				backtomenu->setState( 1 );
			}
		}
	}
	
	
	window->draw( background->get() );
	backtomenu->draw( *window );
	choice->draw( *window );
	worldsize->draw( *window );
	character->draw( window );
	
	if( backtomenu->getState() == 0 )
	{
		music->fadein( 1, sound->getMusicVolume() );
		
		background->fadein( 3 );
		backtomenu->fadein( 3 );
		choice->fadein( 3 );
		character->fadein( 3 );
		worldsize->fadein( 3 );
	}
	else if( backtomenu->getState() == -1 )
	{
		background->fadeout( 3 );
		music->fadeout( 3 );
		backtomenu->fadeout( 3 );
		choice->fadeout( 3 );
		character->fadeout( 3 );
		worldsize->fadeout( 3 );
		
		if( choice->getAlpha() == 0 )
		{
			music->halt();
			backtomenu->setState( 0 );
			state = 2;
		}
	}
	
	else if( backtomenu->getState() == 1 )
	{
		if( character->nextState() )
		{
			music->fadeout( 3 );
			
			background->fadeout( 3 );
			backtomenu->fadeout( 3 );
			choice->fadeout( 3 );
			character->fadeout( 3 );
			worldsize->fadeout( 3 );
			
			if( choice->getAlpha() == 0 )
			{
				music->halt();
				backtomenu->setState( 0 );
				state = 1;
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
	if( state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Level_menu::nextState()
{
	if( state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Level_menu::backToMenu()
{
	if( state == 2 )
	{
		state = 0;
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

int Level_menu::getVegetationsize()
{
	
}