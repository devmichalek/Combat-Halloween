#pragma once

#include "member.h"
#include "drawable/sprite.h"
#include <vector>

class List
{
	vector <MyText*> categories;
	vector <float> categories_x;
	MySprite button;
	
	vector <Member*> develop_members;
	vector <Member*> music_members;
	vector <Member*> chunk_members;
	vector <Member*> sprite_members;
	vector <Member*> font_members;
	vector <Member*> tool_members;
	
public:
	
	List();
	~List();
	void free();
	void reset();
	
	void load( int screen_w, int screen_h );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	void move( float distance );
	
	void freeMembers( vector <Member*> &m );
	void resetMembers( vector <Member*> &m );
	void fillMembers( vector <Member*> &m, string path, int which );
	void drawMembers( vector <Member*> &m, sf::RenderWindow* &window );
	void handleMembers( vector <Member*> &m, sf::Event &event );
	void moveMembers( vector <Member*> &m, float distance );
	void fadeinMembers( vector <Member*> &m, int i = 1, int max = 255 );
	void fadeoutMembers( vector <Member*> &m, int i = 1, int min = 0 );
};