#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include "menu/parentchunk.h"

class Play_button :public Parentchunk
{

protected:

	int state;
	MySprite mySprite;
	MyText myText;
	
public:
	
	Play_button();
    ~Play_button();

    void load( int screen_w, int bot );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	int getBot();
	int getX();
	int getState();
	bool nextGameState();
	
	void fadein( int i, int max );
	void fadeout( int i, int min );
	
	void setState( int s );
};