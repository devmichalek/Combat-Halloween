#include "thread.h"

cmm::Thread::Thread()
{
	thread = nullptr;
	free();
}

cmm::Thread::~Thread()
{
	free();
}

void cmm::Thread::free()
{
	reset();
	success = false;
}

void cmm::Thread::reset()
{
	ready = false;
	if (thread)
	{
		delete thread;
		thread = nullptr;
	}
}