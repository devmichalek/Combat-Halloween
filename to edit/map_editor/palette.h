#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include <vector>

class Palette
{
	int nr;
	MySprite* block;
	
	int text_nr;
	MyText* text;
	
	int which;
	int x, y;
	
	string path;
	string data;
	
	int width; // width of typical block
	int screen_w;
	int screen_h;
	
	bool chosen;
	bool cut;
	bool save;
	bool back;
	bool fix;
	
	int disX, disY;// displacement
	
	vector <MySprite*> v;
	vector <int> v_t;
	
public:
	
	Palette();
    ~Palette();
	void free();

    void load( int screen_w, int screen_h, int number );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	
	int getDisX();
	int getDisY();
	
	bool backToMenu();
	bool saveModeIsOn();
	bool isChosen();
	
	string getPath();
	string getData();
};