#include "core.h"
#include <assert.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "boost/lexical_cast.hpp"

int main(int argc, char** argv)
{
	assert(argc == 6 && "Arguments list should match! (state, R, G, B, A)");

	int state = boost::lexical_cast<int> (argv[1]);
	sf::Uint8 R = boost::lexical_cast<int> (argv[2]);
	sf::Uint8 G = boost::lexical_cast<int> (argv[3]);
	sf::Uint8 B = boost::lexical_cast<int> (argv[4]);
	sf::Uint8 A = boost::lexical_cast<int> (argv[5]);
	// printf("Input: state=%d r=%d g=%d b=%d a=%d\n", state, R, G, B, A);

	sf::Color color(R, G, B, A);
	cmm::Core* core = new cmm::Core(state, color);
	core->create("Combat Halloween");

	sf::CircleShape shape(core->getWidth()/4);
	shape.setFillColor(sf::Color(0xFF - R, 0xFF - G, 0xFF - B));
	shape.setPosition(core->getWidth()/2 - core->getWidth()/4, core->getHeight()/2 - core->getWidth()/4);
	while (core->open)
	{
		// clear
		core->clear();

		// events, mouse, keyboard
		while (core->isEvent())
		{
			if (core->getEvent().type == sf::Event::Closed)
			{
				core->open = false;
			}
		}

		// states, displaying
		core->getWindow()->draw(shape);

		// display
		core->display();
	}
	
	delete core;

	return 0;
}