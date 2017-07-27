#include "menu.h"


Menu::Menu()
{
	free();
}

Menu::~Menu()
{
	free();
}

void Menu::free()
{
	ready = false;
	close = false;
	background.free();
	knight_specs.free();
	github.free();
	scores.free();
	website.free();
	singleplayer.free();
	multiplayer.free();
	exit.free();
	chunkbutton.free();
	musicbutton.free();
	settingsbutton.free();
	pausesystem.free();
	music.free();
}



void Menu::load( float screen_w, float screen_h )
{
	free();
	
	// Set background.
	background.setIdentity( "menu-background" );
	background.load( "images/menu/background.png" );
	background.setScale( screen_w /2560, screen_h /1440 );
	
	// Load "upgrade_knight".
	knight_specs.load( screen_w, screen_h );
	
	// Load link buttons.
	github.load( screen_w /256, screen_h /144, "images/menu/github.png" );
	github.setScale( screen_w /2560, screen_h /1440 );
	github.setUrl( "https://github.com/Adriqun/Combat-Halloween" );
	scores.load( github.getRight() +screen_w /256, screen_h /144, "images/menu/scores.png" );
	scores.setScale( screen_w /2560, screen_h /1440 );
	scores.setUrl( "scores" );
	website.load( scores.getRight() +screen_w /256, screen_h /144, "images/menu/website.png" );
	website.setScale( screen_w /2560, screen_h /1440 );
	website.setUrl( "website" );
	
	// Main buttons.
	singleplayer.load( screen_w /1.8, screen_h /2.35, "images/menu/singleplayer.png" );
	singleplayer.setScale( screen_w /2560, screen_h /1440 );
	multiplayer.load( screen_w /1.8, singleplayer.getBot() +screen_h /72, "images/menu/multiplayer.png", true );
	multiplayer.setScale( screen_w /2560, screen_h /1440 );
	exit.load( screen_w /1.8, multiplayer.getBot() +screen_h /72, "images/menu/exit.png" );
	exit.setScale( screen_w /2560, screen_h /1440 );
	
	// Circle buttons.
	chunkbutton.load( "images/menu/chunk.png", true );
	chunkbutton.set( screen_w -screen_w /256 , screen_h -screen_h /144, screen_w /2560, screen_h /1440 );
	chunkbutton.setPlayable( false );
	musicbutton.load( "images/menu/music.png", true );
	musicbutton.set( chunkbutton.getLeft() -screen_w /256, screen_h -screen_h /144, screen_w /2560, screen_h /1440 );
	musicbutton.setChanged( true );
	settingsbutton.load( "images/menu/settings.png" );
	settingsbutton.set( musicbutton.getLeft() -screen_w /256, screen_h -screen_h /144, screen_w /2560, screen_h /1440 );
	
	// Pause system.
	pausesystem.load( screen_w, screen_h );
	
	// Music.
	music.setIdentity( "menu-music" );
	music.load( "music/menu.ogg" );
	music.setVolume( 0 );
}

void Menu::handle( sf::Event& event )
{
	if( !close )
	{
		if( !pausesystem.isActive() && pausesystem.getAlpha() == 0 )
		{
			knight_specs.handle( event );
			github.handle( event );
			scores.handle( event );
			website.handle( event );
			singleplayer.handle( event );
			multiplayer.handle( event );
			exit.handle( event );
			chunkbutton.handle( event );
			musicbutton.handle( event );
			settingsbutton.handle( event );
		}
		
		pausesystem.handle( event );
	}
}

void Menu::draw( sf::RenderWindow* &window, double elapsedTime )
{
	// fade out -pause
	if( pausesystem.isActive() )
	{
		music.fadeout( elapsedTime *100, 10 );	// <-- CHANGE LATER
		float value = elapsedTime *0xFF;
		float min = 0xFF *3 /4;
		background.fadeout( value, min );
		knight_specs.fadeout( value, min );
		github.fadeout( value, min );
		scores.fadeout( value, min );
		website.fadeout( value, min );
		singleplayer.fadeout( value, min );
		multiplayer.fadeout( value, min );
		exit.fadeout( value, min );
		chunkbutton.fadeout( value, min );
		musicbutton.fadeout( value, min );
		settingsbutton.fadeout( value, min );
		pausesystem.fadein( value *3, min );
	}
	// fade out -close
	else if( close )
	{
		music.fadeout( elapsedTime *100 );
		float value = elapsedTime *0xFF /2;
		background.fadeout( value );
		knight_specs.fadeout( value );
		github.fadeout( value );
		scores.fadeout( value );
		website.fadeout( value );
		singleplayer.fadeout( value );
		multiplayer.fadeout( value );
		exit.fadeout( value );
		chunkbutton.fadeout( value );
		musicbutton.fadeout( value );
		settingsbutton.fadeout( value );
	}
	else // fade in
	{
		music.fadein( elapsedTime *100 );
		float value = elapsedTime *0xFF;
		background.fadein( value );
		knight_specs.fadein( value );
		knight_specs.mechanics( elapsedTime );
		github.fadein( value );
		scores.fadein( value );
		website.fadein( value );
		singleplayer.fadein( value );
		multiplayer.fadein( value );
		exit.fadein( value );
		chunkbutton.fadein( value );
		musicbutton.fadein( value );
		settingsbutton.fadein( value );
		pausesystem.fadeout( value );
	}
	
	// render
	window->draw( background.get() );
	knight_specs.draw( window );
	github.draw( window, elapsedTime );
	scores.draw( window, elapsedTime );
	website.draw( window, elapsedTime );
	singleplayer.draw( window, elapsedTime );
	multiplayer.draw( window, elapsedTime );
	exit.draw( window, elapsedTime );
	chunkbutton.draw( window, elapsedTime );
	musicbutton.draw( window, elapsedTime );
	settingsbutton.draw( window, elapsedTime );
	pausesystem.draw( window, elapsedTime );
	
	// mechanics, rest events
	if( exit.isPressed() ) // close app
	{
		close = true;
	}
	
	if( chunkbutton.isChanged() ) // turn on/off all sounds
	{
		github.setPlayable( chunkbutton.isActive() );
		scores.setPlayable( chunkbutton.isActive() );
		website.setPlayable( chunkbutton.isActive() );
		singleplayer.setPlayable( chunkbutton.isActive() );
		multiplayer.setPlayable( chunkbutton.isActive() );
		exit.setPlayable( chunkbutton.isActive() );
		chunkbutton.setPlayable( !chunkbutton.isActive() );
		musicbutton.setPlayable( chunkbutton.isActive() );
		settingsbutton.setPlayable( chunkbutton.isActive() );
		pausesystem.setPlayable( chunkbutton.isActive() );
	}
	
	if( musicbutton.isChanged() ) // turn on/off music
	{
		musicbutton.isActive() ? music.play() : music.pause();
	}
}



bool Menu::isReady()
{
	return ready;
}

bool Menu::isClose()
{
	if( close && background.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}