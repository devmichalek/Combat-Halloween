#include "hero/activity.h"

Activity::Activity()
{
	line = 0;
	counter = 0;
	active = false;
}

Activity::~Activity()
{
	free();
}

void Activity::free()
{
	line = 0;
	counter = 0;
	active = false;
}

void Activity::summarize()
{
	if( counter >= line )	counter = 0;
	else if( counter > 0 )	counter++;
}