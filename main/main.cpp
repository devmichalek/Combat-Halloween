#include "engine.h"
#include "boost/lexical_cast.hpp"

int main(int argc, char** argv)
{
	std::unique_ptr<Engine> engine;

	if (argc > 1)
	{
		engine = std::make_unique<Engine>(boost::lexical_cast <int> (argv[1]), boost::lexical_cast <int> (argv[2]));
	}
	else
		engine = std::make_unique<Engine>();
	
	engine->loop();
	return EXIT_SUCCESS;
}