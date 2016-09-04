// Adrian Michalek, 2016.07.10 - class Chunk

#pragma once

#include <SDL2/SDL_mixer.h>

class Chunk
{
    Mix_Chunk* chunk;

public:

    Chunk();
    ~Chunk();
    void free();

    bool load( const char* path, int volume = 0 );
    void play();

    Mix_Chunk* get();
    void setVolume( int volume );
};