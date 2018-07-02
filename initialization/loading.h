<<<<<<< HEAD
/**
    loading.h
    Purpose: class Loading - to show progress during loading objects.

    @author Adrian Michalek
    @version 2016.10.05
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/text.h"
#include "drawable/sprite.h"

class Loading
{
	MyText text;			// text "loading"
	sf::Uint8 state;		// show percents
	
	sf::Uint8 counter;		// to set offsets
	sf::Uint8 max;			// how many offset's
	MySprite progress_bar;	// animation
=======
#pragma once
#include "own/text.h"
#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Loading
{
	// Support.
	float screen_w;
	float screen_h;
	bool ready;
	
	// Current progress.
	MyText text;			// Text "loading".
	sf::Uint8 state;		// Show percents.
	
	// Animation
	float counter;		// To set offsets.
	float max;			// How many offset's.
	MySprite progress_bar;
>>>>>>> Combat-Halloween/master
	
public:
	
	// Basics.
	Loading();
	~Loading();
	void free();
<<<<<<< HEAD
	
	void load( unsigned screen_w, unsigned screen_h );	// load textures
	void draw( sf::RenderWindow* &window );	// render textures
	
	// In addition.
	const sf::Uint8& getState() const; 		// getter
=======
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	// In addition, getters.
	const sf::Uint8& getState() const;
	bool isReady();
	
	// Setters.
	void beReady();
	void setText();
>>>>>>> Combat-Halloween/master
};