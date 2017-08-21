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
	knight.free();
	tiles.free();
	objects.free();
	coins.free();
}

void Game::reset()
{
	
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
	
	knight.load( screen_w, screen_h );
	tiles.load( screen_w, screen_h );
	objects.load( screen_w, screen_h );
	coins.load( screen_w, screen_h );
}

void Game::draw( sf::RenderWindow* &window )
{
	window->draw( background.get() );
	objects.draw( window );
	coins.draw( window );
	knight.draw( window );
	tiles.draw( window );
}

void Game::mechanics( double elapsedTime )
{
	knight.mechanics( elapsedTime );
	coins.mechanics( elapsedTime );
	
}



void Game::fadein( float v, int max )
{
	background.fadein( v, max );
	knight.fadein( v, max );
	tiles.fadein( v, max );
	objects.fadein( v, max );
	coins.fadein( v, max );
}

void Game::fadeout( float v, int min )
{
	background.fadeout( v, min );
	knight.fadeout( v, min );
	tiles.fadeout( v, min );
	objects.fadeout( v, min );
	coins.fadeout( v, min );
}



void Game::setUsername( string line )
{
	knight.setUsername( line );
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
		knight.setThread();
		break;
		
		case 2:
		tiles.setThread();
		break;
		
		case 3:
		objects.setThread();
		break;
		
		case 4:
		coins.setThread();
		break;
		
		default:
		
		if( knight.isNull() && tiles.isNull() &&
			objects.isNull() && coins.isNull() )
		{
			loaded = true;
		}
		
		break;
	}
}

int Game::getStatus()
{
	if( loaded )
	{
		if( knight.isReady() && tiles.isReady() &&
			objects.isReady() && coins.isReady() )
		{
			return 2;
		}
		
		return 1;
	}
	
	return 0;
}

void Game::resetStatus()
{
	loaded = false;
}