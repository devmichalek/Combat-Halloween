/**
    reset_button.h
    Purpose: class Reset_button after click reset each txt file, all settings, all money getted etc.

    @author Adrian Michalek
    @version 2017.03.07
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "02_menu/click.h"
#include "01_intro/explanator.h"

class Reset_button :public Click
{
	Explanator explanator;
	mutable sf::Uint8 state;
	mutable MySprite mySprite;
	MyText myText;
	
	bool reset;
	MySprite button;

public:

	Reset_button();
    ~Reset_button();
	void free();

    void load( int screen_w, int bot );
    void draw( sf::RenderWindow* &window );
	void drawButton( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	bool doReset();
	const sf::Uint8& getState() const;
};