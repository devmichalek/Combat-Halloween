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
	menu = false;
	level = false;
	editor = 0;
	run = false;
	alpha = 0;
	
	game.free();
	editorbutton.free();
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
	
	editorbutton.load( "images/editor/back.png" );
	editorbutton.setPosition( screen_w /256 +homebutton.getWidth(), screen_h /144 +homebutton.getHeight(), scale_x, scale_y );
	
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
		if( !menu && !level && editor < 2 && !game.isTable() )
		{
			if( !pausesystem.isActive() && pausesystem.getAlpha() == 0 )
			{
				chat.handle( event );
			
				if( !chat.isOpen() )
				{
					game.handle( event );
					
					if( editor == 0 )
					{
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
					else
					{
						editorbutton.handle( event );
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
		
		if( loading_world.backToPrevious() )
		{
			if( editor == 1 )	editor = 2;
			else				level = true;
		}
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
		loading_world.mechanics( elapsedTime );
		loading_world.draw( window );
		
		if( loading_world.ableData() )
		{
			game.setMessage( loading_world.getData() );
		}
		else if( !loading_world.getStop() && loading_world.getReady() > 0 )
		{
			game.loading( loading_world.getState() );
			if( game.getStatus() == 1 )
			{
				loading_world.setError( game.getLoadingError() );
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
	
	if( editor == 0 )
	{
		homebutton.draw( window );
		levelbutton.draw( window );
		chunkbutton.draw( window );
		musicbutton.draw( window );
		chunk_volume.draw( window );
		music_volume.draw( window );
	}
	else
	{
		editorbutton.draw( window );
	}
	
	chat.draw( window );
	pausesystem.draw( window );
}

void Play::mechanics( double elapsedTime )
{
	// Mechanics.
	if( !pausesystem.isActive() && !menu && !level && editor < 2 && !game.isTable() )
	{
		if( !chat.isOpen() )
		{
			game.mechanics( elapsedTime );
		}
		
		chat.mechanics( elapsedTime );
		
		if( chat.isCommand() )
		{
			// Someone clicked backtomenu button.
			if( chat.findCommand( "@menu" ) && editor == 0 )
			{
				homebutton.setChanged( true );
			}
			
			// Someone clicked level button.
			else if( chat.findCommand( "@back" ) )
			{
				if( editor == 0 )
				{
					levelbutton.setChanged( true );
				}
				else
				{
					editor = 2;
					editorbutton.setChanged( true );
				}
			}
			
			// Someone clicked level button.
			else if( chat.findCommand( "@edit" ) || chat.findCommand( "@editor" ) )
			{
				if( editor == 1 )
				{
					editor = 2;
					editorbutton.setChanged( true );
				}
			}
			
			// Someone clicked level button.
			else if( chat.findCommand( "@commit suicide" ) && editor == 0 )
			{
				game.commitSuicide();
				chat.isOpen() = false;
			}
			
			// Turn on/off all chunks.
			else if( chat.findCommand( "@chunk" ) && editor == 0 )
			{
				chunkbutton.setChanged( true );
				chunkbutton.setActive( !chunkbutton.isActive() );
			}
			
			// Turn on/off music.
			else if( chat.findCommand( "@music" ) && editor == 0 )
			{
				musicbutton.setChanged( true );
				musicbutton.setActive( !musicbutton.isActive() );
			}
			
			// Turn on/off all sounds.
			else if( chat.findCommand( "@sound" ) && editor == 0 )
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
		
		// Someone clicked level button.
		else if( levelbutton.isChanged() )
		{
			chat.isOpen() = false;
			level = true;
		}
		
		// Someone clicked editor button.
		else if( editorbutton.isChanged() )
		{
			chat.isOpen() = false;
			editor = 2;
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
		float min = 0xFF *3 /4;
		float value = elapsedTime *0xFF *2;
		
		if( alpha > min )
		{
			alpha -= value;
			if( alpha < min )	alpha = min;
			
			game.setAlpha( alpha );
			homebutton.fadeout( value, min );
			levelbutton.fadeout( value, min );
			chunkbutton.fadeout( value, min );
			musicbutton.fadeout( value, min );
			chunk_volume.fadeout( value, min );
			music_volume.fadeout( value, min );
			chat.fadeout( value, min );
		}
		
		pausesystem.fadein( value *3, min );
		music.fadeout( elapsedTime *100, music_volume.getMainVolume() *0.2 );
	}
	
	// Fade out - closed.
	else if( menu || level || editor == 2 || game.isTable() )
	{
		if( alpha > 0 )
		{
			float value = elapsedTime *0xFF;
			alpha -= value;
			if( alpha < 0 )	alpha = 0;
			
			game.setAlpha( alpha );
			homebutton.fadeout( value );
			levelbutton.fadeout( value );
			chunkbutton.fadeout( value );
			musicbutton.fadeout( value );
			chunk_volume.fadeout( value );
			music_volume.fadeout( value );
			chat.fadeout( value );
		}
		
		music.fadeout( elapsedTime *100 );
	}
	
	// Fade in.
	else
	{
		float value = elapsedTime *0xFF *2;
		if( alpha < 0xFF )
		{
			alpha += value;
			if( alpha > value )	alpha = 0xFF;
			
			game.setAlpha( alpha );
			homebutton.fadein( value );
			levelbutton.fadein( value );
			chunkbutton.fadein( value );
			musicbutton.fadein( value );
			chunk_volume.fadein( value );
			music_volume.fadein( value );
		}
		
		pausesystem.fadeout( value );
		music.fadein( elapsedTime *100, music_volume.getMainVolume() );
	}
}



void Play::setMessage( string message )
{
	if( message[ 0 ] == '0' && editor == 0 )
	{
		editor = 1;
	}
	
	loading_world.setMessage( message );
	loading_world.setThread();
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
	editor = 0;
	run = false;
	alpha = 0;
	
	// Reset.
	game.reset();
	homebutton.setActive( false );
	levelbutton.setActive( false );
	editorbutton.setActive( false );
	loading_world.setMessage( "" );
	loading_world.reset();
	chat.reset();
	music.stop();
}



bool Play::isMenu()
{
	if( menu && alpha == 0 )
	{
		return true;
	}
	
	return false;
}

bool Play::isLevel()
{
	if( level && alpha == 0 )
	{
		return true;
	}
	
	return false;
}

bool Play::isTable()
{
	if( game.isTable() && alpha == 0 )
	{
		return true;
	}
	
	return false;
}

bool Play::isEditor()
{
	if( editor == 2 && alpha == 0 )
	{
		return true;
	}
	
	return false;
}