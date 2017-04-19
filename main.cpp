/**
    main.cpp
    Purpose: Create engine, call loop then delete.

    @author Adrian Michalek
    @version 2016.08.14
	@email adrmic98@gmail.com
*/

#include "engine.h"

int main( int argc, char** argv )
{
    Engine* engine = new Engine;

	engine->loop();

    delete engine;
    engine = NULL;

    return EXIT_SUCCESS;
}