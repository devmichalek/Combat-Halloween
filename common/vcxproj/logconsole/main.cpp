#include "logconsole.h"

int main(int argc, char** argv)
{
	try
	{
		throw std::string("blah blah\n");
	}
	catch (std::string msg)
	{
		// ...
	}
	
	return 0;
}