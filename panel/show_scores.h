#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"

class Show_scores
{
	unsigned screen_w;
	unsigned screen_h;
	int max, number, vel;
	int state;
	
	MySprite line;
	MyText summary;
	
	MyText status;
	MyText status_word;
	
	MyText coruption;
	MyText coruption_word;
	
	MyText world;
	MyText world_word;
	
	MyText money;
	MyText money_word;
	
	MyText mine;
	MyText mine_word;
	
	MyText time;
	MyText time_word;
	
	MyText scores;
	MyText scores_word;
	
public:
	
	Show_scores();
	~Show_scores();
	void free();
	
	void load( unsigned screen_w, unsigned screen_h, float y );
	void draw( sf::RenderWindow* &window );
	
	void setScores( int s );
	void setResult( bool r );
	string setCoruption( sf::Uint8 c );
	string setWorld( sf::Uint8 w );
	void setMoney( int m );
	void setMine( int m, sf::Uint8 w );
	void setTimePlayed( string t );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
};