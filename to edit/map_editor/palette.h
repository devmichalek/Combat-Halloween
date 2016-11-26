#pragma once

#include "templates/sprite.h"
#include "templates/text.h"

class Palette
{
	string folder_name;
	int width; // width of typical block
	
	int nr;
	MySprite* block;
	
	int which;
	int x, y;
	
	int text_nr;
	MyText* text;
	
	bool chosenOn;
	bool deleteOn;
	bool saveOn;
	bool back;
	
	int disX, disY;// displacement
	
public:
	
	Palette();
    ~Palette();
	void free();

    void load( int screen_w, int screen_h, int num );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	bool backtomenu();
	string getFolder();
	bool saveIsOn();
	
	int getDisX();
	int getDisY();
	bool chosenIsOn();
};