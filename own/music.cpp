#include "music.h"

Music::Music()
{
	identity = "";
    music = NULL;
}

Music::~Music()
{
    free();
}

void Music::free()
{
    if( music != NULL )
    {
        delete music;
        music = NULL;
    }
}

const sf::Music* Music::get() const
{
    return music;
}



void Music::setIdentity( string identity )
{
	this->identity = identity;
}

const string& Music::getIdentity() const
{
	return identity;
}



void Music::load( string path )
{
    free();
	
	try
	{
		music = new sf::Music;
		if( !music->openFromFile( path ) )
		{
			throw identity + " not found music " + path;
		}
		else
		{
			music->setLoop( true );
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}



void Music::fadein( float v, int max )
{
	if( music->getVolume() < max )
	{
		float newVolume = music->getVolume() +v;
		
		if( newVolume > max )
		{
			newVolume = max;
		}
		
		music->setVolume( newVolume );
	}
}

void Music::fadeout( float v, int min )
{
	if( music->getVolume() > min )
	{
		float newVolume = music->getVolume() -v;
		
		if( newVolume < min )
		{
			newVolume = min;
		}
		
		music->setVolume( newVolume );
	}
}



void Music::stop()
{
	music->stop();
}

void Music::play()
{
	music->play();
}

void Music::pause()
{
	music->pause();
}

void Music::setVolume( float volume )
{
	music->setVolume( volume );
}