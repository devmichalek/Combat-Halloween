#include "engine.h"

int main()
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->loop();
	return EXIT_SUCCESS;
}