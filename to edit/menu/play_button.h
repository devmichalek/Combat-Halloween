#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "menu/parentchunk.h"

class Play_button :public Parentchunk
{

protected:

	mutable int state;
	mutable MySprite mySprite;
	MyText myText;
	
public:
	
	Play_button();
    ~Play_button();

    void load( int screen_w, int bot );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	const int getBot() const;
	const int getX() const;
	const int& getState() const;
	bool nextGameState() const;
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	void setState( const int s );	// mutator
};