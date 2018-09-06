#include "thread.h"
#include <stdio.h>
#include <limits>
#include <iostream>

void counting(const char* t, int s, int e, bool &r, bool &v)
{
	for (int i = s; i < e; ++i)
	{
		printf("%s: %d\n", t, i);
	}

	// now is ready for the next task
	r = true;

	// set status
	v = true;
}

int main(int argc, char** argv)
{
	cmm::Thread t1;
	cmm::Thread t2;

	t1.thread = new std::thread(counting, "Thread 1", 0, 10, std::ref(t1.success), std::ref(t1.ready));
	t1.thread->detach();
	t2.thread = new std::thread(counting, "Thread 2", 10, 20, std::ref(t1.success), std::ref(t2.ready));
	t2.thread->detach();

	while (1)
	{
		if (t1.ready && t2.ready)	// if thread finish its task
			break;
	}

	// Print status
	// if (t1.success && t2.success)	printf("Success...\n");
	// else								printf("Error...\n");
	
	// Finish
	std::cout << "Press Enter to Continue...\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Free
	t1.free();
	t2.free();

	return 0;
}