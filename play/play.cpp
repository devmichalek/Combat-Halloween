#include "play.h"
#include "own/file.h"

Play::Play()
{
	free();
}

Play::~Play()
{
	free();
}

void Play::free()
{
	level = false;
	menu = false;
	run = false;
	
	game.free();
	homebutton.free();
	levelbutton.free();
	chunkbutton.free();
	musicbutton.free();
	chunk_volume.free();
	music_volume.free();
	loading_world.free();
	chat.free();
	pausesystem.free();
	music.free();
}

void Play::load( float screen_w, float screen_h )
{
	free();
	
	float scale_x = 0.5;
	float scale_y = 0.5;
	
	
	// Load game.
	game.load( screen_w, screen_h );
	
	// Circle buttons.
	homebutton.load( "images/level/home.png" );
	homebutton.setPosition( screen_w /256 , screen_h /144 +homebutton.getHeight(), scale_x, scale_y );
	homebutton.setPosition( screen_w /256 +homebutton.getWidth(), screen_h /144 +homebutton.getHeight(), scale_x, scale_y );
	levelbutton.load( "images/play/level.png" );
	levelbutton.setPosition( homebutton.getRight() +screen_w /256 +homebutton.getWidth(), screen_h /144 +homebutton.getHeight(), scale_x, scale_y );
	chunkbutton.load( "images/menu/chunk.png", true );
	chunkbutton.setPosition( screen_w -screen_w /256 , screen_h /144 +homebutton.getHeight(), scale_x, scale_y );
	musicbutton.load( "images/menu/music.png", true );
	musicbutton.setPosition( chunkbutton.getLeft() -screen_w /256, screen_h /144 +homebutton.getHeight(), scale_x, scale_y );
	
	// Set volume buttons.
	chunk_volume.load( chunkbutton.getLeft(), chunkbutton.getRight(), chunkbutton.getBot(), screen_w, screen_h );
	music_volume.load( musicbutton.getLeft(), musicbutton.getRight(), musicbutton.getBot(), screen_w, screen_h );
	
	// Set loader.
	loading_world.load( screen_w, screen_h );
	
	// Set chat.
	chat.load( screen_w, screen_h, 1 );
	chat.setCommandColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	chat.setTypicalColor( sf::Color( 0xBA, 0xBA, 0xBA ) );
	
	// Pause system.
	pausesystem.load( screen_w, screen_h );
	
	// Music.
	music.setIdentity( "play-music" );
	music.load( "music/play.ogg" );
}

void Play::handle( sf::Event& event )
{
	if( loading_world.isReady() )
	{
		if( !menu && !level && !game.isTable() )
		{
			if( !pausesystem.isActive() && pausesystem.getAlpha() == 0 )
			{
				chat.handle( event );
			
				if( !chat.isOpen() )
				{
					game.handle( event );
					homebutton.handle( event );
					levelbutton.handle( event );
					
					if( !chunk_volume.handle( event ) )
					{
						chunkbutton.handle( event );
					}
					
					if( !music_volume.handle( event ) )
					{
						musicbutton.handle( event );
					}
				}
			}
			
			if( !chat.isOpen() )
			{
				pausesystem.handle( event );
			}
		}
	}
	else
	{
		loading_world.handle( event );
	}
}

void Play::head( sf::RenderWindow* &window, double elapsedTime )
{
	if( loading_world.isReady() )
	{
		mechanics( elapsedTime );
		fades( elapsedTime );
		draw( window );
	}
	
	// Loading tiles etc. - show status.
	else
	{
		loading_world.draw( window, elapsedTime );
		if( !loading_world.getStop() )
		{
			game.loading( loading_world.getState() );
			if( game.getStatus() == 1 )
			{
				loading_world.setError();
			}
			else if( game.getStatus() == 2 )
			{
				loading_world.setSuccess();
			}
			
			game.resetStatus();
		}
	}
}



void Play::draw( sf::RenderWindow* &window )
{
	game.draw( window );
	homebutton.draw( window );
	levelbutton.draw( window );
	chunkbutton.draw( window );
	musicbutton.draw( window );
	chunk_volume.draw( window );
	music_volume.draw( window );
	chat.draw( window );
	pausesystem.draw( window );
}

void Play::mechanics( double elapsedTime )
{
	// Mechanics.
	if( !pausesystem.isActive() && !menu && !level && !game.isTable() )
	{
		if( !chat.isOpen() )
		{
			game.mechanics( elapsedTime );
		}
		
		chat.mechanics( elapsedTime );
		
		if( chat.isCommand() )
		{
			// Someone clicked backtomenu button.
			if( chat.findCommand( "@menu" ) )
			{
				homebutton.setChanged( true );
			}
			
			// Someone clicked level button.
			else if( chat.findCommand( "@back" ) )
			{
				levelbutton.setChanged( true );
			}
			
			// Someone clicked level button.
			else if( chat.findCommand( "@commit suicide" ) )
			{
				game.commitSuicide();
				chat.isOpen() = false;
			}
			
			// Turn on/off all chunks.
			else if( chat.findCommand( "@chunk" ) )
			{
				chunkbutton.setChanged( true );
				chunkbutton.setActive( !chunkbutton.isActive() );
			}
			
			// Turn on/off music.
			else if( chat.findCommand( "@music" ) )
			{
				musicbutton.setChanged( true );
				musicbutton.setActive( !musicbutton.isActive() );
			}
			
			// Turn on/off all sounds.
			else if( chat.findCommand( "@sound" ) )
			{
				chunkbutton.setChanged( true );
				chunkbutton.setActive( !chunkbutton.isActive() );
				musicbutton.setChanged( true );
				musicbutton.setActive( !musicbutton.isActive() );
			}
			
			// game
			else if( chat.findCommand( "@collision" ) )
			{
				game.turnCollision( !game.getCollision() );
			}
			else if( chat.findCommand( "@fps" ) )
			{
				game.turnFPS( !game.getFPS() );
			}
			
			// Command doesn't exist.
			else
			{
				chat.setError();
			}
		}
			
		// Someone clicked home button.
		if( homebutton.isChanged() )
		{
			chat.isOpen() = false;
			menu = true;
		}
		
		// Someone clicked play button.
		else if( levelbutton.isChanged() )
		{
			chat.isOpen() = false;
			level = true;
		}
		
		chunk_volume.mechanics( elapsedTime );
		music_volume.mechanics( elapsedTime );
		
		// Turn on/off all sounds.
		if( chunkbutton.isChanged() )
		{
			game.setPlayable( chunkbutton.isActive() );
			homebutton.setPlayable( chunkbutton.isActive() );
			levelbutton.setPlayable( chunkbutton.isActive() );
			chunkbutton.setPlayable( !chunkbutton.isActive() );
			musicbutton.setPlayable( chunkbutton.isActive() );
			chunk_volume.setPlayable( chunkbutton.isActive() );
			music_volume.setPlayable( chunkbutton.isActive() );
			chunk_volume.setActive( chunkbutton.isActive() );
			pausesystem.setPlayable( chunkbutton.isActive() );
		}
		
		// Volume of sounds is changed.
		if( chunk_volume.isChanged() )
		{
			float value = chunk_volume.getMainVolume();
			game.setVolume( value );
			homebutton.setVolume( value );
			levelbutton.setVolume( value );
			chunkbutton.setVolume( value );
			musicbutton.setVolume( value );
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

void Play::fades( double elapsedTime )
{
	// Fade out - paused.
	if( pausesystem.isActive() )
	{
		float value = elapsedTime *0xFF *2;
		float min = 0xFF *3 /4;
		
		game.fadeout( value, min );
		homebutton.fadeout( value, min );
		levelbutton.fadeout( value, min );
		chunkbutton.fadeout( value, min );
		musicbutton.fadeout( value, min );
		chunk_volume.fadeout( value, min );
		music_volume.fadeout( value, min );
		chat.fadeout( value, min );
		pausesystem.fadein( value *3, min );
		
		music.fadeout( elapsedTime *100, music_volume.getMainVolume() *0.2 );
	}
	
	// Fade out - closed.
	else if( menu || level || game.isTable() )
	{
		float value = elapsedTime *0xFF;
		
		game.fadeout( value );
		homebutton.fadeout( value );
		levelbutton.fadeout( value );
		chunkbutton.fadeout( value );
		musicbutton.fadeout( value );
		chunk_volume.fadeout( value );
		music_volume.fadeout( value );
		chat.fadeout( value );
		
		music.fadeout( elapsedTime *100 );
	}
	
	// Fade in.
	else
	{
		float value = elapsedTime *0xFF *2;
		
		game.fadein( value );
		homebutton.fadein( value );
		levelbutton.fadein( value );
		chunkbutton.fadein( value );
		musicbutton.fadein( value );
		chunk_volume.fadein( value );
		music_volume.fadein( value );
		pausesystem.fadeout( value );
		
		music.fadein( elapsedTime *100, music_volume.getMainVolume() );
	}
}



void Play::setUsername( string line )
{
	game.setUsername( line );
}
	
void Play::loadSound()
{
	if( !run && loading_world.isReady() )
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
			game.setVolume( chunkVolume );
			homebutton.setVolume( chunkVolume );
			levelbutton.setVolume( chunkVolume );
			chunkbutton.setVolume( chunkVolume );
			musicbutton.setVolume( chunkVolume );
			chunk_volume.setVolume( chunkVolume );
			chunk_volume.setMainVolume( chunkVolume );
			music_volume.setVolume( chunkVolume );
			pausesystem.setVolume( chunkVolume );
			
			// Music.
			music.setVolume( musicVolume );
			music_volume.setMainVolume( musicVolume );
			
			// Set playable.
			game.setPlayable( chunkPlay );
			homebutton.setPlayable( chunkPlay );
			levelbutton.setPlayable( chunkPlay );
			chunkbutton.setPlayable( !chunkPlay );
			chunkbutton.setActive( chunkPlay );
			musicbutton.setPlayable( chunkPlay );
			musicbutton.setActive( musicPlay );
			chunk_volume.setPlayable( chunkPlay );
			music_volume.setPlayable( chunkPlay );
			pausesystem.setPlayable( chunkPlay );
			musicPlay ? music.play() : music.pause();
		}
		
		file.free();
	}
}

void Play::saveSound()
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
	
	// plus
	menu = false;
	level = false;
	run = false;
	
	// Reset.
	game.reset();
	homebutton.setActive( false );
	levelbutton.setActive( false );
	loading_world.reset();
	chat.reset();
	music.stop();
}



bool Play::isMenu()
{
	if( menu && game.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

bool Play::isLevel()
{
	if( level && game.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

bool Play::isTable()
{
	if( game.isTable() && game.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}