#pragma once
#include <thread>

namespace cmm
{
	struct Thread final
	{
		bool ready;		// ready to start next action
		bool success;	// thread finished action with success
		std::thread* thread;

		explicit Thread();
		~Thread();
		void free();
		void reset();
	};
}