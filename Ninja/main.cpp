#include "engine.h"
#include <stdio.h>

int main()
{
    Engine* engine = new Engine;

    if( !engine->load() )
    {
        printf( "Not created engine!\n" );
    }
    else
    {
        engine->loop();
    }

    delete engine;
    engine = NULL;

    return EXIT_SUCCESS;
}
