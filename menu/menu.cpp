#include "menu.h"
#include "own/file.h"

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
	run = false;
	
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
	settings.free();
	chunk_volume.free();
	music_volume.free();
	pausesystem.free();
	music.free();
}



void Menu::load( float screen_w, float screen_h )
{
	free();
	
	// Load background.
	background.setIdentity( "menu-background" );
	background.load( "images/menu/background.png" );
	background.setScale( screen_w /2560, screen_h /1440 );
	
	// Load "knight specs".
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
	singleplayer.load( screen_w /1.9, screen_h /2.35, "images/menu/singleplayer.png" );
	singleplayer.setScale( screen_w /2560, screen_h /1440 );
	multiplayer.load( screen_w /1.9, singleplayer.getBot() +screen_h /72, "images/menu/multiplayer.png", true );
	multiplayer.setScale( screen_w /2560, screen_h /1440 );
	exit.load( screen_w /1.9, multiplayer.getBot() +screen_h /72, "images/menu/exit.png" );
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
	
	// Settings.
	settings.load( screen_w, screen_h );
	
	// Set volume buttons.
	chunk_volume.load( chunkbutton.getLeft(), chunkbutton.getRight(), chunkbutton.getBot(), screen_w, screen_h );
	music_volume.load( musicbutton.getLeft(), musicbutton.getRight(), musicbutton.getBot(), screen_w, screen_h );
	
	// Pause system.
	pausesystem.load( screen_w, screen_h );
	
	// Music.
	music.setIdentity( "menu-music" );
	music.load( "music/menu.ogg" );
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
			settingsbutton.handle( event );
			settings.handle( event );
			
			if( !chunk_volume.handle( event ) )
			{
				chunkbutton.handle( event );
			}
			
			if( !music_volume.handle( event ) )
			{
				musicbutton.handle( event );
			}
		}
		
		pausesystem.handle( event );
	}
}

void Menu::head( sf::RenderWindow* &window, double elapsedTime )
{
	mechanics( elapsedTime );
	fades( elapsedTime );
	draw( window );
}



void Menu::draw( sf::RenderWindow* &window )
{
	window->draw( background.get() );
	knight_specs.draw( window );
	github.draw( window );
	scores.draw( window );
	website.draw( window );
	singleplayer.draw( window );
	multiplayer.draw( window );
	exit.draw( window );
	chunkbutton.draw( window );
	musicbutton.draw( window );
	settingsbutton.draw( window );
	settings.draw( window );
	chunk_volume.draw( window );
	music_volume.draw( window );
	pausesystem.draw( window );
}

void Menu::mechanics( double elapsedTime )
{
	// Mechanics.
	if( !pausesystem.isActive() )
	{
		knight_specs.mechanics( elapsedTime );
		
		// Close application.
		if( exit.isPressed() )
		{
			close = true;
		}
		
		// Exsert / shovel settings.
		if( settingsbutton.isActive() )
		{
			settings.exsertTable( elapsedTime );
		}
		else
		{
			settings.shovelTable( elapsedTime );
		}
		
		settings.mechanics( elapsedTime );
		
		// Turn on/off all sounds.
		if( chunkbutton.isChanged() )
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
			settings.setPlayable( chunkbutton.isActive() );
			chunk_volume.setPlayable( chunkbutton.isActive() );
			music_volume.setPlayable( chunkbutton.isActive() );
			chunk_volume.setActive( chunkbutton.isActive() );
			pausesystem.setPlayable( chunkbutton.isActive() );
		}
		
		// Volume of sounds is changed.
		if( chunk_volume.isChanged() )
		{
			float value = chunk_volume.getMainVolume();
			knight_specs.setVolume( value );
			github.setVolume( value );
			scores.setVolume( value );
			website.setVolume( value );
			singleplayer.setVolume( value );
			multiplayer.setVolume( value );
			exit.setVolume( value );
			chunkbutton.setVolume( value );
			musicbutton.setVolume( value );
			settingsbutton.setVolume( value );
			chunk_volume.setVolume( value );
			music_volume.setVolume( value );
			pausesystem.setVolume( value );
		}
		
		// Turn on/off music.
		if( musicbutton.isChanged() )
		{
			musicbutton.isActive() ? music.play() : music.pause();
			music_volume.setActive( musicbutton.isActive() );
		}
		
		// Volume of music is changed.
		if( music_volume.isChanged() )
		{
			music.setVolume( music_volume.getMainVolume() );
		}
	}
}

void Menu::fades( double elapsedTime )
{
	// Fade out - paused.
	if( pausesystem.isActive() )
	{
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
		settings.fadeout( value, min );
		chunk_volume.fadeout( value, min );
		music_volume.fadeout( value, min );
		pausesystem.fadein( value *3, min );
		
		music.fadeout( elapsedTime *100, music_volume.getMainVolume() *0.2 );
	}
	
	// Fade out - closed.
	else if( close )
	{
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
		settings.fadeout( value );
		chunk_volume.fadeout( value );
		music_volume.fadeout( value );
		
		music.fadeout( elapsedTime *100 );
	}
	
	// Fade in.
	else
	{
		float value = elapsedTime *0xFF;
		
		background.fadein( value );
		knight_specs.fadein( value );
		github.fadein( value );
		scores.fadein( value );
		website.fadein( value );
		singleplayer.fadein( value );
		multiplayer.fadein( value );
		exit.fadein( value );
		chunkbutton.fadein( value );
		musicbutton.fadein( value );
		settingsbutton.fadein( value );
		settings.fadein( value );
		chunk_volume.fadein( value );
		music_volume.fadein( value );
		pausesystem.fadeout( value );
		
		music.fadein( elapsedTime *100, music_volume.getMainVolume() );
	}
}



void Menu::loadSound()
{
	if( !run )
	{
		run = true;
		
		float chunkVolume = 0;
		float musicVolume = 0;
		bool chunkPlay = false;
		bool musicPlay = false;
		
		MyFile file;
		file.load( "txt/sound.txt" );
		if( file.is_good() )
		{
			string line = "";
			file.get() >> line; chunkVolume = con::stof( line );
			file.get() >> line; musicVolume = con::stof( line );
			file.get() >> line; chunkPlay = con::stoi( line );
			file.get() >> line; musicPlay = con::stoi( line );
			
			// The rest.
			// printf( "%f %f %d %d\n", chunkVolume, musicVolume, chunkPlay, musicPlay );
			
			// Chunk.
			knight_specs.setVolume( chunkVolume );
			github.setVolume( chunkVolume );
			scores.setVolume( chunkVolume );
			website.setVolume( chunkVolume );
			singleplayer.setVolume( chunkVolume );
			multiplayer.setVolume( chunkVolume );
			exit.setVolume( chunkVolume );
			chunkbutton.setVolume( chunkVolume );
			musicbutton.setVolume( chunkVolume );
			settingsbutton.setVolume( chunkVolume );
			settings.setVolume( chunkVolume );
			chunk_volume.setVolume( chunkVolume );
			chunk_volume.setMainVolume( chunkVolume );
			music_volume.setVolume( chunkVolume );
			
			// Music.
			music.setVolume( musicVolume );
			music_volume.setMainVolume( musicVolume );
			
			// Set playable.
			knight_specs.setPlayable( chunkPlay );
			github.setPlayable( chunkPlay );
			scores.setPlayable( chunkPlay );
			website.setPlayable( chunkPlay );
			singleplayer.setPlayable( chunkPlay );
			multiplayer.setPlayable( chunkPlay );
			exit.setPlayable( chunkPlay );
			chunkbutton.setPlayable( chunkPlay );
			chunkbutton.setActive( chunkPlay );
			musicbutton.setPlayable( chunkPlay );
			musicbutton.setActive( musicPlay );
			settingsbutton.setPlayable( chunkPlay );
			settings.setPlayable( chunkPlay );
			chunk_volume.setPlayable( chunkPlay );
			music_volume.setPlayable( chunkPlay );
			musicPlay ? music.play() : music.pause();
		}
		
		file.free();
	}
}

void Menu::saveSound()
{
	MyFile file;
	file.load( "txt/sound.txt" );
	if( file.is_good() )
	{
		string line = con::itos( chunk_volume.getMainVolume() ); file.get() << line << endl;
		line = con::itos( music_volume.getMainVolume() ); file.get() << line << endl;
		line = con::itos( chunkbutton.isActive() ); file.get() << line << endl;
		line = con::itos( musicbutton.isActive() ); file.get() << line;
	}
	
	file.free();
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