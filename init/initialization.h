<<<<<<< HEAD
/**
    initialazation.h
    Purpose: class Initialization - contains nick stuff.

    @author Adrian Michalek
    @version 2017.04.22
	@email adrmic98@gmail.com
*/

#pragma once

#include "nick_setter.h"
#include "nick_info.h"

class Initialization
{
	bool next;
	
	Nick_setter nick_setter;
	Nick_info nick_info;
=======
#pragma once
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class Initialization
{
	enum	// Enum with states of texts.
	{
		AUTHOR = 0,
		PRESENTS,
		HALLOWEEN,
		COMBAT,
		AMOUNT
	};
	
	bool ready;
	sf::Uint8 state;
	vector <MyText*> texts;
>>>>>>> Combat-Halloween/master
	
public:
	
	// Basics.
	Initialization();
<<<<<<< HEAD
    ~Initialization();
    void free();
	
    void load( unsigned screen_w, unsigned screen_h );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	// Extra.
	bool nextState();
=======
	~Initialization();
	void free();
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	// Next state.
	bool isReady();
>>>>>>> Combat-Halloween/master
};