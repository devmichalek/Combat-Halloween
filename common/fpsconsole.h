#pragma once
#include <SFML/System/Clock.hpp>

namespace cmm
{
	// Usage: If timePassed() - checks whether amount of set time elapsed (do update every n sec), then getFPS()
	class FPSConsole
	{
	protected:
		sf::Clock clock;
		float currentTime;
		float fps;

		double counter;
		double max;
	public:
		FPSConsole();
		~FPSConsole();
		void mechanics(const double &elapsedTime);
		bool timePassed();
		const float& getFPS();
	};
}