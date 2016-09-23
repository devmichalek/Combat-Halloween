#include "level/levelmenu.h"

Level_menu::Level_menu()
{
	state = 0;
	playmusic = true;
	playchunk = true;
	musicvolume = 0;
	chunkvolume = 0;
	
	select = new Select;
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
}

void Level_menu::setStartPackage( bool a, bool b, sf::Uint8 cv, sf::Uint8 mv )
{
	playmusic = a;
	playchunk = b;
	chunkvolume = cv;
	musicvolume = mv;
}
	
void Level_menu::load( int screen_w, int screen_h )
{
	select->load( screen_w, screen_h );
	
	// Set music
	
	// Set chunks
	if( !playchunk )
	{
		select->turn();
	}
	
	// Set music volume
	
	// Set chunk volume
	select->setVolume( chunkvolume );
	
	
}


void Level_menu::handle( sf::Event &event )
{
	select->handle( event );
}

void Level_menu::draw( sf::RenderWindow* &window )
{
	select->draw( window );
	
	select->fadein( 3, 255 );
}

	
bool Level_menu::isQuit()
{
	if( state == 2 )
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