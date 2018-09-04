#include "logconsole.h"

std::vector<std::string> LogConsole::container;

LogConsole::LogConsole()
{
	// ...
}

LogConsole::~LogConsole()
{
	clear();
}

void LogConsole::clear()
{
	if (!container.empty())
	{
		container.clear();
		container.shrink_to_fit();
	}
}



void LogConsole::addMessage(std::string msg)
{
	container.push_back("Message: " + msg);
}

void LogConsole::addWarning(std::string war)
{
	container.push_back("Warning: " + war);
}

void LogConsole::addError(std::string err)
{
	container.push_back("Error: " + err);
}