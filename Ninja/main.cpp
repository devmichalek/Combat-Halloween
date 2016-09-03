#include "engine.h"
#include <stdio.h>

int main( int argc, char** argv )
{
    Engine* engine = new Engine;

    //if( !engine->load() )
    //{
    //    printf( "Not created engine!\n" );
    //}

	engine->loop();


    delete engine;
    engine = NULL;

    return EXIT_SUCCESS;
}
