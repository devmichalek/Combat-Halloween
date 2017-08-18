#include "Game.h"
#include "own/file.h"

Game::Game()
{
	free();
}

Game::~Game()
{
	free();
}

void Game::free()
{
	table = false;
	loaded = false;
	
	background.free();
}



void Game::load( float screen_w, float screen_h )
{
	free();
	
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	// Load background.
	background.setIdentity( "game-background" );
	background.load( "images/play/background.png" );
	background.setScale( scale_x, scale_y );
}

void Game::draw( sf::RenderWindow* &window )
{
	window->draw( background.get() );
}

void Game::mechanics( double elapsedTime )
{
	
}



void Game::fadein( float v, int max )
{
	background.fadein( v, max );
}

void Game::fadeout( float v, int min )
{
	background.fadeout( v, min );
}



void Game::setPlayable( bool playable )
{
	
}

void Game::setVolume( float volume )
{
	
}



bool Game::isTable()
{
	if( table && background.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

float Game::getAlpha()
{
	return background.getAlpha();
}



void Game::loading( int which )
{
	switch( which )
	{
		case 1:
		
		break;
		
		case 101:
		loaded = true;
		break;
	}
}

bool Game::isError()
{
	if( loaded )
	{
		loaded = false;
		
		if( true )
		{
			return true;
		}
	}
	
	return false;
}

bool Game::isSuccess()
{
	if( loaded )
	{
		loaded = false;
		
		if( true )
		{
			return true;
		}
	}
	
	return false;
}