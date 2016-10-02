#pragma once

#include <SFML/Graphics/Color.hpp>

class State
{

public:
	
	int state;
	bool mSwitch;
	bool cSwitch;
	sf::Uint8 mVolume;
	sf::Uint8 cVolume;
	
	State( int state = 0, bool mSwitch = true, bool cSwitch = true, sf::Uint8 mVolume = 0, sf::Uint8 cVolume = 0 );
	~State();
	
	void operator =( State* state );
};