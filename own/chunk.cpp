#include "chunk.h"

Chunk::Chunk()
{
	identity = "";
	chunk = NULL;
	buffer = NULL;
}

Chunk::~Chunk()
{
    free();
}

void Chunk::free()
{
    if( chunk != NULL )
    {
        delete chunk;
        chunk = NULL;
    }
	
	if( buffer != NULL )
    {
        delete buffer;
        buffer = NULL;
    }
}

const sf::Sound* Chunk::get() const
{
    return chunk;
}



void Chunk::setIdentity( string identity )
{
	this->identity = identity;
}

const string& Chunk::getIdentity() const
{
	return identity;
}




void Chunk::load( string path )
{
    free();
	
	try
	{
		buffer = new sf::SoundBuffer;
		if( !buffer->loadFromFile( path ) )
		{
			throw identity + " not found chunk from " + path;
		}
		else
		{
			chunk = new sf::Sound;
			chunk->setBuffer( *buffer );
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}




void Chunk::stop()
{
	chunk->stop();
}

void Chunk::play()
{
	chunk->play();
}

void Chunk::pause()
{
	chunk->pause();
}

void Chunk::setVolume( float volume )
{
	chunk->setVolume( volume );
}