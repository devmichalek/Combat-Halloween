#include "engine.h"

int main( int argc, char **argv )
{
	Engine* engine = new Engine;

	engine->loop();

    delete engine;
    engine = NULL;
	
	return EXIT_SUCCESS;
}