<<<<<<< HEAD
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
	bonus_choice = new Bonus_choice;
=======
#include "level.h"
#include "own/file.h"

Level::Level()
{
	free();
>>>>>>> Combat-Halloween/master
}

Level::~Level()
{
	free();
}

void Level::free()
{
<<<<<<< HEAD
	sound.free();
	delete background;
	delete music;
	delete backtomenu;
	delete choice;
	delete character;
	delete cube;
	delete difficulty;
	delete bonus_choice;
}



void Level::load( unsigned screen_w, unsigned screen_h )
{
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	background->load( "data/menu/background.png" );
	music->load( "data/level/music.mp3" );
	backtomenu->load( screen_w );
	choice->load();
	bonus_choice->load();
}

void Level::loadCharacter()
{
	character->load( screen_w, screen_h );
}

void Level::loadWorlds()
{
	choice->reset( screen_w, screen_h );
	bonus_choice->reset( choice->getLeft(), choice->getBot(), choice->getWidth() );
	
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
		bonus_choice->handle( event );
	}
	else if( !character->nextState() )
	{
		if( backtomenu->getState() == 1 )
		{
			character->handle( event );
			backtomenu->handle( event );
=======
	back = false;
	next = false;
	run = false;
	
	background.free();
	worldtable.free();
	homebutton.free();
	playbutton.free();
	updatebutton.free();
	chunkbutton.free();
	musicbutton.free();
	chunk_volume.free();
	music_volume.free();
	chat.free();
	pausesystem.free();
	music.free();
}

void Level::load( float screen_w, float screen_h )
{
	free();
	
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	// Load background.
	background.setIdentity( "level-background" );
	background.load( "images/level/background.png" );
	background.setScale( scale_x, scale_y );
	
	// Load world table.
	worldtable.load( screen_w, screen_h );
	
	// Circle buttons.
	homebutton.load( "images/level/home.png" );
	homebutton.setPosition( screen_w /256 , screen_h /144 +homebutton.getHeight(), scale_x, scale_y );
	homebutton.setPosition( screen_w /256 +homebutton.getWidth(), screen_h /144 +homebutton.getHeight(), scale_x, scale_y );
	playbutton.load( "images/level/play.png" );
	playbutton.setPosition( screen_w -screen_w /256 , screen_h /144 +homebutton.getHeight(), scale_x, scale_y );
	updatebutton.load( "images/level/update.png" );
	updatebutton.setPosition( homebutton.getRight() +screen_w /256 +homebutton.getWidth(), screen_h /144 +homebutton.getHeight(), scale_x, scale_y );
	chunkbutton.load( "images/menu/chunk.png", true );
	chunkbutton.setPosition( screen_w -screen_w /256 , screen_h -screen_h /144, scale_x, scale_y );
	musicbutton.load( "images/menu/music.png", true );
	musicbutton.setPosition( chunkbutton.getLeft() -screen_w /256, screen_h -screen_h /144, scale_x, scale_y );
	
	// Set volume buttons.
	chunk_volume.load( chunkbutton.getLeft(), chunkbutton.getRight(), chunkbutton.getBot(), screen_w, screen_h );
	music_volume.load( musicbutton.getLeft(), musicbutton.getRight(), musicbutton.getBot(), screen_w, screen_h );
	
	// Set chat.
	chat.load( screen_w, screen_h );
	chat.setCommandColor( sf::Color( 0, 0, 0 ) );
	chat.setTypicalColor( sf::Color( 0x68, 0x68, 0x68 ) );
	
	// Pause system.
	pausesystem.load( screen_w, screen_h );
	
	// Music.
	music.setIdentity( "level-music" );
	music.load( "music/level.ogg" );
}

void Level::handle( sf::Event& event )
{
	if( !next && !back )
	{
		if( !pausesystem.isActive() && pausesystem.getAlpha() == 0 )
		{
			chat.handle( event );
			
			if( !chat.isOpen() )
			{
				homebutton.handle( event );
			
				if( worldtable.isChosen() )
				{
					playbutton.handle( event );
				}
				
				worldtable.handle( event );
				updatebutton.handle( event );
				
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
>>>>>>> Combat-Halloween/master
		}
	}
}

<<<<<<< HEAD
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
			int v = -1;
			for( int g = 0; g < 10; g++ )
			{
				character->move( v, 0 );
				cube->move( v, -screen_w );
				difficulty->move( v, -screen_w );
				bonus_choice->move( v, -screen_w );
				if( choice->move( v, -screen_w ) )
				{
					backtomenu->setState( 1 );
				}
			}
		}
	}
	
	
	window->draw( background->get() );
	choice->draw( *window );
	cube->draw( *window );
	difficulty->draw( *window );
	character->draw( window );
	backtomenu->draw( *window );
	bonus_choice->draw( *window );
	
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
		bonus_choice->fadein( v );
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
		bonus_choice->fadeout( v );
		
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
			bonus_choice->fadeout( v );
			
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
		sf::Uint8 v = 1;
		for( int g = 0; g < 10; g++ )
		{
			character->move( v, screen_w );
			cube->move( v, 0 );
			difficulty->move( v, 0 );
			bonus_choice->move( v, 0 );
			if( choice->move( v, 0 ) )
			{
				choice->reset( screen_w, screen_h );
				backtomenu->setState( 0 );
			}
=======
void Level::head( sf::RenderWindow* &window, double elapsedTime )
{
	mechanics( elapsedTime );
	fades( elapsedTime );
	draw( window );
}



void Level::draw( sf::RenderWindow* &window )
{
	window->draw( background.get() );
	worldtable.draw( window );
	homebutton.draw( window );
	
	if( worldtable.isChosen() || next )
	{
		playbutton.draw( window );
	}
	
	updatebutton.draw( window );
	chunkbutton.draw( window );
	musicbutton.draw( window );
	chunk_volume.draw( window );
	music_volume.draw( window );
	chat.draw( window );
	pausesystem.draw( window );
}

void Level::mechanics( double elapsedTime )
{
	// Mechanics.
	if( !pausesystem.isActive() && !next && !back )
	{
		chat.mechanics( elapsedTime );
		if( chat.isCommand() )
		{
			// Someone clicked backtomenu button.
			if( chat.findCommand( "@menu" ) || chat.findCommand( "@back" ) )
			{
				homebutton.setChanged( true );
			}
			
			// Someone clicked play.
			else if( chat.findCommand( "@play" ) || chat.findCommand( "@start" ) )
			{
				if( worldtable.isChosen() )
				{
					playbutton.setChanged( true );
				}
			}
			
			// Reload data.
			else if( chat.findCommand( "@reload" ) || chat.findCommand( "@connect" ) ||
			chat.findCommand( "@rel" ) || chat.findCommand( "@con" ) )
			{
				if( worldtable.abletoreload() )
				{
					
					worldtable.setThread();
				}
			}
			
			// Update data.
			else if( chat.findCommand( "@update" ) )
			{
				updatebutton.setChanged( true );
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
			back = true;
		}
		
		// Someone clicked play button.
		else if( playbutton.isChanged() )
		{
			chat.isOpen() = false;
			next = true;
		}
		
		// update data
		if( updatebutton.isChanged() )
		{
			updatebutton.setActive( false );
			worldtable.reload();
			worldtable.setThread();
		}
		
		chunk_volume.mechanics( elapsedTime );
		music_volume.mechanics( elapsedTime );
		
		// Turn on/off all sounds.
		if( chunkbutton.isChanged() )
		{
			homebutton.setPlayable( chunkbutton.isActive() );
			playbutton.setPlayable( chunkbutton.isActive() );
			updatebutton.setPlayable( chunkbutton.isActive() );
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
			homebutton.setVolume( value );
			playbutton.setVolume( value );
			updatebutton.setVolume( value );
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
>>>>>>> Combat-Halloween/master
		}
	}
}

<<<<<<< HEAD


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
		bonus_choice->turnOff();
	}
	else
	{
		backtomenu->turnOn();
		choice->turnOn();
		character->turnOn();
		cube->turnOn();
		difficulty->turnOn();
		bonus_choice->turnOn();
		
		// Set chunk volume
		backtomenu->setVolume( sound.getChunkVolume() );
		choice->setVolume( sound.getChunkVolume() );
		character->setVolume( sound.getChunkVolume() );
		cube->setVolume( sound.getChunkVolume() );
		difficulty->setVolume( sound.getChunkVolume() );
		bonus_choice->setVolume( sound.getChunkVolume() );
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
	bonus_choice->reset( choice->getLeft(), choice->getBot(), choice->getWidth() );
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

int Level::getBonus_world()
{
	return bonus_choice->getResult();
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
=======
void Level::fades( double elapsedTime )
{
	// Fade out - paused.
	if( pausesystem.isActive() )
	{
		float value = elapsedTime *0xFF *2;
		float min = 0xFF *3 /4;
		
		background.fadeout( value, min );
		worldtable.fadeout( value, min );
		homebutton.fadeout( value, min );
		playbutton.fadeout( value, min );
		updatebutton.fadeout( value, min );
		chunkbutton.fadeout( value, min );
		musicbutton.fadeout( value, min );
		chunk_volume.fadeout( value, min );
		music_volume.fadeout( value, min );
		chat.fadeout( value, min );
		pausesystem.fadein( value *3, min );
		
		music.fadeout( elapsedTime *100, music_volume.getMainVolume() *0.2 );
	}
	
	// Fade out - closed.
	else if( next || back )
	{
		float value = elapsedTime *0xFF *2;
		
		background.fadeout( value );
		worldtable.fadeout( value );
		homebutton.fadeout( value );
		playbutton.fadeout( value );
		updatebutton.fadeout( value );
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
		
		background.fadein( value );
		worldtable.fadein( value );
		homebutton.fadein( value );
		playbutton.fadein( value );
		updatebutton.fadein( value );
		chunkbutton.fadein( value );
		musicbutton.fadein( value );
		chunk_volume.fadein( value );
		music_volume.fadein( value );
		pausesystem.fadeout( value );
		
		music.fadein( elapsedTime *100, music_volume.getMainVolume() );
	}
}



void Level::setUsername( string line )
{
	worldtable.setUsername( line );
	chat.setUsername( line );
}

void Level::loadSound()
{
	if( !run )
	{
		run = true;
		
		// Set thread.
		worldtable.setThread();
		
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
			worldtable.setVolume( chunkVolume );
			homebutton.setVolume( chunkVolume );
			playbutton.setVolume( chunkVolume );
			updatebutton.setVolume( chunkVolume );
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
			worldtable.setPlayable( chunkPlay );
			homebutton.setPlayable( chunkPlay );
			playbutton.setPlayable( chunkPlay );
			updatebutton.setPlayable( chunkPlay );
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

void Level::saveSound()
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
	back = false;
	next = false;
	run = false;
	
	// Reset.
	homebutton.setActive( false );
	playbutton.setActive( false );
	updatebutton.setActive( false );
	worldtable.reset();
	chat.reset();
	music.stop();
}



bool Level::isNext()
{
	if( next && background.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

bool Level::isBack()
{
	if( back && background.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
>>>>>>> Combat-Halloween/master
}