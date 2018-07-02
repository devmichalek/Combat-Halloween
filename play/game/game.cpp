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
	message = "";
	
	moving_bg.free();
	knight.free();
	eye.free();
	tiles.free();
	objects.free();
	coins.free();
	lightbulbs.free();
	skeletons.free();
	zombies.free();
}

void Game::reset()
{
	table = false;
	loaded = false;
	message = "";
	
	knight.reset();
	eye.reset( knight.getRect().left +knight.getRect().width/2, knight.getRect().top -knight.getRect().height );
	tiles.reset();
	objects.reset();
	coins.reset();
	lightbulbs.reset();
	skeletons.reset();
	zombies.reset();
}



void Game::load( float screen_w, float screen_h )
{
	free();
	
	moving_bg.load( screen_w, screen_h, 0 );
	knight.load( screen_w, screen_h );
	eye.load( screen_w, screen_h );
	tiles.load( screen_w, screen_h );
	objects.load( screen_w, screen_h );
	coins.load( screen_w, screen_h );
	lightbulbs.load( screen_w, screen_h );
	skeletons.load( screen_w, screen_h, 0, "skeleton" );
	zombies.load( screen_w, screen_h, 2, "zombie" );
	
	reset();
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
	moving_bg.draw( window, lightbulbs.getShader() );
	window->setView( knight.getView() );
	coins.draw( window, lightbulbs.getShader() );
	knight.draw( window, lightbulbs.getShader() );
	tiles.draw( window, lightbulbs.getShader() );
	skeletons.draw( window, lightbulbs.getShader() );
	zombies.draw( window, lightbulbs.getShader() );
	objects.draw( window, lightbulbs.getShader() );
	eye.draw( window, lightbulbs.getShader() );
	window->setView( window->getDefaultView() );
	objects.drawFPS( window );
}

void Game::mechanics( double elapsedTime )
{
	if( !knight.isDeath() )
	{
		knight.jumping( elapsedTime );
		if( tiles.checkCollisionRect( knight.getRect() ) )
		{
			knight.backjumping( elapsedTime );
		}
		
		knight.gravity( elapsedTime );
		tiles.tickGravity( knight.getRect(), elapsedTime );
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
			else
			{
				moving_bg.mechanics( elapsedTime, 1 );
			}
		}
		else if( knight.moveRight( elapsedTime ) )
		{
			if( tiles.checkCollisionRect( knight.getRect() ) || knight.getRight() > tiles.getBorderX() +tiles.getScreenWidth() )
			{
				knight.back( elapsedTime );
			}
			else
			{
				moving_bg.mechanics( elapsedTime, -1 );
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
	
	// Knight the rest.
	if( knight.isAttacking() )
	{
		skeletons.harm( knight.getAttackRect(), knight.getDamage() );
		zombies.harm( knight.getAttackRect(), knight.getDamage() );
	}
	knight.animation( elapsedTime );
	
	// Coins and lightbulbs.
	coins.mechanics( elapsedTime );
	lightbulbs.mechanics( elapsedTime );
	
	
	// Skeletons
	skeletons.walk( knight.getRect(), elapsedTime );
	if( skeletons.isHarmed( knight.getRect() ) )
	{
		knight.harm( skeletons.getDamage() );
	}
	skeletons.mechanics( elapsedTime );
	
	// Zombies
	zombies.walk( knight.getRect(), elapsedTime );
	if( zombies.isHarmed( knight.getRect() ) )
	{
		knight.harm( zombies.getDamage() );
	}
	zombies.mechanics( elapsedTime );
	
	// Set borders.
	tiles.setBorderX( knight.getViewX() );
	tiles.setBorderY( knight.getViewY() );
	objects.setBorderX( knight.getViewX() );
	objects.setBorderY( knight.getViewY() );
	coins.setBorderX( knight.getViewX() );
	coins.setBorderY( knight.getViewY() );
	lightbulbs.setBorderX( knight.getViewX() );
	lightbulbs.setBorderY( knight.getViewY() );
	
	// Foes borders.
	skeletons.setBorderX( knight.getViewX() );
	skeletons.setBorderY( knight.getViewY() );
	zombies.setBorderX( knight.getViewX() );
	zombies.setBorderY( knight.getViewY() );
	
	eye.setPosition( knight.getRect().left +knight.getRect().width/2, knight.getRect().top -knight.getRect().height );
	eye.mechanics( elapsedTime );
	objects.mechanics( elapsedTime );
}

void Game::setAlpha( float alpha )
{
	lightbulbs.setAlpha( alpha );
}

void Game::setMessage( string message )
{
	this->message = message;
	printf( "%d\n", message.size() );
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



void Game::loading( int which )
{
	switch( which )
	{
		case 1:
		printf( "setthread\n" );
		knight.setThread( message );
		break;
		
		case 2:
		tiles.setThread( message );
		break;
		
		case 3:
		objects.setThread( message );
		break;
		
		case 4:
		coins.setThread( message );
		break;
		
		case 5:
		lightbulbs.setThread( message );
		break;
		
		case 6:
		skeletons.setThread( message );
		break;
		
		case 7:
		zombies.setThread( message );
		break;
		
		default:
		if( knight.isNull() && tiles.isNull() &&
			objects.isNull() && coins.isNull() &&
			lightbulbs.isNull() && skeletons.isNull() &&
			zombies.isNull() )
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
			objects.isReady() && coins.isReady() &&
			lightbulbs.isReady() && skeletons.isReady() &&
			zombies.isReady() )
		{
			eye.reset( knight.getRect().left +knight.getRect().width/2, knight.getRect().top -knight.getRect().height );
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

string Game::getLoadingError()
{
	string addError = "";
	
	if( !knight.isReady() )				addError += knight.getError();
	else if( !tiles.isReady() )			addError += tiles.getError();
	else if( !objects.isReady() )		addError += objects.getError();
	else if( !coins.isReady() )			addError += coins.getError();
	else if( !lightbulbs.isReady() )	addError += lightbulbs.getError();
	else if( !skeletons.isReady() )		addError += skeletons.getError();
	else if( !zombies.isReady() )		addError += zombies.getError();
	
	return addError;
}



void Game::turnCollision( bool collision )
{
	knight.turnCollision( collision );
	tiles.turnCollision( collision );
	skeletons.turnCollision( collision );
	zombies.turnCollision( collision );
}

bool Game::getCollision()
{
	return skeletons.getCollision();
}

void Game::turnFPS( bool fps )
{
	objects.setFPS( fps );
}

bool Game::getFPS()
{
	return objects.getFPS();
}

void Game::commitSuicide()
{
	knight.commitSuicide();
}