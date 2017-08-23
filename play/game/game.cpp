#include "Game.h"
#include "own/file.h"
#include <SFML/Graphics/RectangleShape.hpp>
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
	table = false;
	loaded = false;
	
	knight.reset();
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

void Game::handle( sf::Event& event )
{
	if( !knight.isDeath() )
	{
		knight.handle( event );
	}
}

void Game::draw( sf::RenderWindow* &window )
{
	window->draw( background.get() );
	window->setView( knight.getView() );
	coins.draw( window );
	objects.draw( window );
	knight.draw( window );
	tiles.draw( window );
	objects.drawFront( window );
	window->setView( window->getDefaultView() );
	
	/*
	sf::RectangleShape rectshape;
	rectshape.setSize( sf::Vector2f( knight.getRect().width, knight.getRect().height ) );
	rectshape.setPosition( sf::Vector2f( knight.getRect().left, knight.getRect().top ) );
	window->draw( rectshape );
	*/
}

void Game::mechanics( double elapsedTime )
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::A ) )
	{
		knight.commitSuicide();
	}
	
	if( !knight.isDeath() )
	{
		knight.jumping( elapsedTime );
		if( tiles.checkCollisionRect( knight.getRect() ) )
		{
			knight.gravity( elapsedTime );
		}
		
		knight.gravity( elapsedTime );
		if( tiles.checkCollisionRect( knight.getRect() ) )
		{
			knight.weightlessness( elapsedTime );
		}
		
		if( knight.jump() )
		{
			
		}
		
		if( knight.attack() )
		{
			
		}
		
		if( knight.moveLeft( elapsedTime ) )
		{
			if( tiles.checkCollisionRect( knight.getRect() ) || knight.getLeft() < tiles.getBorderX() )
			{
				knight.back( elapsedTime );
			}
		}
		else if( knight.moveRight( elapsedTime ) )
		{
			if( tiles.checkCollisionRect( knight.getRect() ) || knight.getRight() > tiles.getBorderX() +tiles.getScreenWidth() )
			{
				knight.back( elapsedTime );
			}
		}
		else
		{
			knight.idle( elapsedTime );
		}
	}
	else if( knight.isRemains() )
	{
		table = true;
	}
	
	knight.animation( elapsedTime );
	coins.mechanics( elapsedTime );
	
	// Set borders.
	tiles.setBorderX( knight.getViewX() );
	tiles.setBorderY( knight.getViewY() );
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
	return table;
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