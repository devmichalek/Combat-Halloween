#include "level/levelmenu.h"

Level_menu::Level_menu()
{
	state = 0;
	which_level = -1;
	playmusic = true;
	playchunk = true;
	musicvolume = 0;
	chunkvolume = 0;
	
	select = new Select;
	background = new MySprite;
	music = new Music;
	backtomenu = new Backtomenu( "", false );
}

Level_menu::~Level_menu()
{
	free();
}

void Level_menu::free()
{
	state = 0;
	playmusic = true;
	playchunk = true;
	musicvolume = 0;
	chunkvolume = 0;
	
	delete select;
	delete background;
	delete music;
	delete backtomenu;
}

void Level_menu::setStartPackage( bool a, bool b, sf::Uint8 cv, sf::Uint8 mv )
{
	playmusic = a;
	playchunk = b;
	chunkvolume = cv;
	musicvolume = mv;
	
	// Set chunks
	if( !playchunk )
	{
		select->turn();
		backtomenu->turn();
	}
	
	// Set music volume
	music->setVolume( musicvolume );
	
	// Set chunk volume
	select->setVolume( chunkvolume );
	backtomenu->setVolume( chunkvolume );
}
	
void Level_menu::load( int screen_w, int screen_h )
{
	select->load( screen_w, screen_h );
	background->load( "menu/background.png" );
	music->load( "level select/Rayman Legends OST - Mysterious Swamps .mp3" );
	backtomenu->load( screen_w );
}


void Level_menu::handle( sf::Event &event )
{
	select->handle( event );
	backtomenu->handle( event );
}

void Level_menu::draw( sf::RenderWindow* &window )
{
	if( playmusic )
		music->play();
	
	window->draw( background->get() );
	select->draw( window );
	backtomenu->draw( *window );
	
	if( backtomenu->getState() == 0 && select->nextState() == -1 )
	{
		select->fadein( 3, 255 );
		background->fadein( 3, 255 );
		music->fadein( 1, musicvolume );
		backtomenu->fadein( 3, 255 );
	}
	else if( backtomenu->getState() == 1 )
	{
		select->fadeout( 3, 0 );
		background->fadeout( 3 );
		music->fadeout( 3 );
		backtomenu->fadeout( 3, 0 );
		
		if( background->getAlpha() == 0 )
		{
			music->halt();
			state = 2;
		}
	}
	else if( select->nextState() != -1 )
	{
		select->fadeout( 3, 0 );
		background->fadeout( 3 );
		music->fadeout( 3 );
		backtomenu->fadeout( 3, 0 );
		
		if( background->getAlpha() == 0 )
		{
			which_level = select->nextState();
			music->halt();
			state = 1;
		}
	}
}

	
bool Level_menu::isQuit()
{
	if( state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Level_menu::nextState()
{
	if( state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Level_menu::backToMenu()
{
	if( state == 2 )
		return true;
		
	return false;
}



bool Level_menu::musicOn()
{
	return playmusic;
}

bool Level_menu::chunkOn()
{
	return playchunk;
}

sf::Uint8 Level_menu::getChunkVolume()
{
	return chunkvolume;
}

sf::Uint8 Level_menu::getMusicVolume()
{
	return musicvolume;
}

int Level_menu::getLevel()
{
	// printf( "%d\n", which_level );
	return which_level;
}