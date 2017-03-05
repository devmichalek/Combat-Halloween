#pragma once

#include "02_menu/development/develop.h"
#include <vector>

class Development
{
	vector <Develop*> develops;
	vector <int> levels;
	vector <float> values;
	vector <float> costs;
	int bank;
	
	MyText skill;
	MyText level;
	MyText value;
	MyText upgrade;
	
	MyText bank_text;
	MyText money;
	
public:
	
	Development();
    ~Development();
	void free();

    void load( int bot, int screen_h );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	string multiply( int which ); // rules
	float multiplyCost( int which );
	
	// other
	void setVolume( int volume );
	void turn();
};