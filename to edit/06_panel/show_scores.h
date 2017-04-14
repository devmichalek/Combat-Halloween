#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"

class Show_scores
{
	int screen_w;
	int screen_h;
	int max, number, vel;
	int state;
	
	MySprite line;
	MyText summary;
	
	MyText status;
	MyText status_word;
	
	MyText coruption;
	MyText coruption_word;
	MySprite coruption_dot;
	
	MyText world;
	MyText world_word;
	MySprite world_sprite;
	
	MyText money;
	MyText money_word;
	MySprite money_sprite;
	
	MyText mine;
	MyText mine_word;
	MySprite mine_sprite;
	
	MyText time;
	MyText time_word;
	
	MyText scores;
	MyText scores_word;
	
public:
	
	Show_scores();
	~Show_scores();
	void free();
	
	void load( int screen_w, int screen_h, int t );
	void draw( sf::RenderWindow* &window );
	
	void setScores( int s );
	void setResult( bool r );
	void setCoruption( sf::Uint8 c );
	void setWorld( sf::Uint8 w );
	void setMoney( int m );
	void setMine( int m, sf::Uint8 w );
	void setTimePlayed( string t );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
};