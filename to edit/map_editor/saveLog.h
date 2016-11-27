#pragma once

#include "templates/sprite.h"
#include "templates/text.h"
#include <fstream>

class SaveLog
{
	MySprite bar;
	
	MyText limb;
	MyText editable;
	
	MyText save;
	MySprite savebar;
	
	string name;
	string path;
	bool action;
	
	fstream file;
	
	string data;
	int platform;
	
public:
	
	SaveLog();
    ~SaveLog();
	void free();

    void load( int screen_w, int screen_h, string folder );
    void draw( sf::RenderWindow* &window );
    void handle( sf::Event &event );
	
	void saveAsFile();
	void supplyData( string data );
	void supplyPlatform( int p );
};