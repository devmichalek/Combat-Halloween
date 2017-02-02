/**
    levelmenu.h
    Purpose: class Level_menu - huge object which contains stuff drawable in level state.

    @author Adrian Michalek
    @version 2016.12.20
	@email adrmic98@gmail.com
*/

#include "levelmenu.h"

Level_menu::Level_menu()
{
	state = 0;
	
	// Create level menu objects
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
	sound.free();
	delete background;
	delete music;
	delete backtomenu;
	delete choice;
	delete character;
	delete worldsize;
}



void Level_menu::load( unsigned screen_w, unsigned screen_h )
{
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
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
	if( sound.getMusicPlay() && state == 0 )
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
		music->fadein( 1, sound.getMusicVolume() );
		
		sf::Uint8 v = 2;
		
		background->fadein( v );
		backtomenu->fadein( v );
		choice->fadein( v );
		character->fadein( v );
		worldsize->fadein( v );
	}
	else if( backtomenu->getState() == -1 )
	{
		sf::Uint8 v = 3;
		
		background->fadeout( v );
		music->fadeout( v );
		backtomenu->fadeout( v );
		choice->fadeout( v );
		character->fadeout( v );
		worldsize->fadeout( v );
		
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
			sf::Uint8 v = 3;
			
			music->fadeout( v );
			
			background->fadeout( v );
			backtomenu->fadeout( v );
			choice->fadeout( v );
			character->fadeout( v );
			worldsize->fadeout( v );
			
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
		sf::Uint8 v = 20;
		character->move( v, screen_w );
		worldsize->move( v, 0 );
		if( choice->move( v, 0 ) )
		{
			choice->reset( screen_w, screen_h );
			backtomenu->setState( 0 );
		}
	}
}



void Level_menu::setSound()
{
	// Set chunks
	if( !sound.getChunkPlay() )
	{
		backtomenu->turnOff();
		choice->turnOff();
		worldsize->turnOff();
	}
	
	// Set music volume
	music->setVolume( sound.getMusicVolume() );
	
	// Set chunk volume
	backtomenu->setVolume( sound.getChunkVolume() );
	choice->setVolume( sound.getChunkVolume() );
	character->setVolume( sound.getChunkVolume() );
	worldsize->setVolume( sound.getChunkVolume() );
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
		return true;
	}
		
	return false;
}

void Level_menu::reset()
{
	state = 0;
	backtomenu->setState( 0 );
	choice->reset( screen_w, screen_h );
	worldsize->reset( screen_w, screen_h );
	character->reset( screen_w, screen_h );
}

void Level_menu::reloadMusic()
{
	music->reload();
	Mix_HaltMusic();
}



int Level_menu::getWorld()
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
