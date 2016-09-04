// Adrian Michalek, 2016.07.10 - class Chunk

#include "chunk.h"
#include <stdio.h>

Chunk::Chunk()
{
    chunk = NULL;
}

Chunk::~Chunk()
{
    free();
}

void Chunk::free()
{
    if( chunk != NULL )
    {
        Mix_FreeChunk( chunk );
        chunk = NULL;
    }
}


bool Chunk::load( const char* path, int volume )
{
    bool success = true;

    free();

    chunk = Mix_LoadWAV( path );
    if( chunk == NULL )
    {
        printf( "Not found chunk %s\n", path );
        printf( "Error %s\n", Mix_GetError() );
        success = false;
    }
    else if( volume != 0 )
    {
        Mix_VolumeChunk( chunk, volume );
    }

    return success;
}

void Chunk::play()
{
    Mix_PlayChannel( -1, chunk, 0 );
}


Mix_Chunk* Chunk::get()
{
    return chunk;
}

void Chunk::setVolume( int volume )
{
    Mix_VolumeChunk( chunk, volume );
}
