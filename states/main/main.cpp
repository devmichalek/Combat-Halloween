#include "engine.h"
#include "loading.h"

int main(int argc, char** argv)
{
	std::unique_ptr<Engine> engine;

	engine = std::make_unique<Engine>();

	if (Loading::isError())
		return EXIT_FAILURE;
	
	engine->loading_loop();

	engine->main_loop();

	return EXIT_SUCCESS;
}