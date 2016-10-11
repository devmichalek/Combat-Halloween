#include "engine.h"
#include <stdio.h>

int main( int argc, char** argv )
{
    Engine* engine = new Engine;

    engine->load();
	engine->loop();


    delete engine;
    engine = NULL;

    return EXIT_SUCCESS;
}