/**
    level.h
    Purpose: class Level - huge object which contains stuff drawable in level state.

    @author Adrian Michalek
    @version 2016.12.20
	@email adrmic98@gmail.com
*/

#include "level.h"

Level::Level()
{
	state = 0;
	
	// Create level menu objects
	background = new MySprite;
	music = new Music;
	backtomenu = new Backtomenu( "", false );
	choice = new Choice;
	character = new Character;
	cube = new Cube;
	difficulty = new Difficulty;
}

Level::~Level()
{
	free();
}

void Level::free()
{
	sound.free();
	delete background;
	delete music;
	delete backtomenu;
	delete choice;
	delete character;
	delete cube;
	delete difficulty;
}



void Level::load( unsigned screen_w, unsigned screen_h )
{
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	background->load( "data/02_menu/background.png" );
	music->load( "data/03_level/music.mp3" );
	backtomenu->load( screen_w );
	choice->load( screen_w, screen_h );
}

void Level::loadCharacter()
{
	character->load( screen_w, screen_h );
}

void Level::loadWorlds()
{
	choice->reset( screen_w, screen_h );
	
	cube->load( choice->getLeft(), choice->getBot() );
	difficulty->load( cube->getRight(), cube->getTop() );
}

void Level::handle( sf::Event &event )
{
	if( !choice->isChosen() && backtomenu->getState() == 0 )
	{
		choice->handle( event );
		cube->handle( event );
		difficulty->handle( event );
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

void Level::draw( sf::RenderWindow* &window )
{
	if( sound.getMusicPlay() && state == 0 )
	{
		music->play();
	}
	
	
	if( backtomenu->getState() == 0 )
	{
		if( choice->isChosen() )
		{
			character->move( -10, 0 );
			cube->move( -10, -screen_w );
			difficulty->move( -10, -screen_w );
			if( choice->move( -10, -screen_w ) )
			{
				backtomenu->setState( 1 );
			}
		}
	}
	
	
	window->draw( background->get() );
	choice->draw( *window );
	cube->draw( *window );
	difficulty->draw( *window );
	character->draw( window );
	backtomenu->draw( *window );
	
	if( backtomenu->getState() == 0 )
	{
		music->fadein( 1, sound.getMusicVolume() );
		
		sf::Uint8 v = 2;
		
		background->fadein( v );
		backtomenu->fadein( v );
		choice->fadein( v );
		character->fadein( v );
		cube->fadein( v );
		difficulty->fadein( v );
	}
	else if( backtomenu->getState() == -1 )
	{
		sf::Uint8 v = 3;
		
		background->fadeout( v );
		music->fadeout( v );
		backtomenu->fadeout( v );
		choice->fadeout( v );
		character->fadeout( v );
		cube->fadeout( v );
		difficulty->fadeout( v );
		
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
			cube->fadeout( v );
			difficulty->fadeout( v );
			
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
		sf::Uint8 v = 10;
		character->move( v, screen_w );
		cube->move( v, 0 );
		difficulty->move( v, 0 );
		if( choice->move( v, 0 ) )
		{
			choice->reset( screen_w, screen_h );
			backtomenu->setState( 0 );
		}
	}
}



void Level::setSound()
{
	// Set chunks
	if( !sound.getChunkPlay() )
	{
		backtomenu->turnOff();
		choice->turnOff();
		character->turnOff();
		cube->turnOff();
		difficulty->turnOff();
	}
	else
	{
		backtomenu->turnOn();
		choice->turnOn();
		character->turnOn();
		cube->turnOn();
		difficulty->turnOn();
		
		// Set chunk volume
		backtomenu->setVolume( sound.getChunkVolume() );
		choice->setVolume( sound.getChunkVolume() );
		character->setVolume( sound.getChunkVolume() );
		cube->setVolume( sound.getChunkVolume() );
		difficulty->setVolume( sound.getChunkVolume() );
	}
	
	// Set music volume
	music->setVolume( sound.getMusicVolume() );
}
	
bool Level::isQuit()
{
	if( state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Level::nextState()
{
	if( state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Level::backToMenu()
{
	if( state == 2 )
	{
		return true;
	}
		
	return false;
}

void Level::reset()
{
	state = 0;
	backtomenu->setState( 0 );
	choice->reset( screen_w, screen_h );
	character->reset( screen_w, screen_h );
	cube->reset( choice->getLeft(), choice->getBot() );
	difficulty->load( cube->getRight(), cube->getTop() );
}

void Level::reloadMusic()
{
	music->reload();
	Mix_HaltMusic();
}



int Level::getWorld()
{
	return choice->getResult() +3;
}

int Level::getCharacter()
{
	return character->getResult();
}

int Level::getWorldsize()
{
	return cube->getWorldSize();
}

int Level::getFlatness()
{
	// printf( "%d\n", cube->getFlatness() );
	return cube->getFlatness();
}

int Level::getDifficulty()
{
	// printf( "%d\n", difficulty->getDifficulty() );
	return difficulty->getDifficulty();
}