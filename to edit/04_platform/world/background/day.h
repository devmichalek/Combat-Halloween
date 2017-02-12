#pragma once

#include <SFML/Graphics/Color.hpp>
#include <vector>

using namespace std;

class Day
{
	enum
	{
		I = 17,
		F = 20,
		S = 35,
		N = 40
	};
	
	bool change;
	bool count;
	
	sf::Uint8 state;
	sf::Uint8 counter;
	sf::Uint8 sec;
	sf::Uint8 line;
	
	sf::Uint8 r, g, b;
	vector <sf::Color> colors;
	
public:

	Day();
	~Day();
	void free();
	void reset();
	
	void set();
	void setInTime();
	void mechanics();
	
	bool isChange();
	sf::Color getColor();
};