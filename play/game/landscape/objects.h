#pragma once
#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <thread>

class Objects
{
	// Basics.
	float screen_w;
	float screen_h;
	float border_x;
	float border_y;
	
	vector <MySprite*> sprites;
	vector <sf::Vector2f> fs;
	vector <sf::Uint8> types;
	
	// Thread stuff.
	std::thread* myThread;
	bool thread_ready;
	bool ready;
	
public:
	
	// Basics.
	Objects();
	~Objects();
	void free();
	void reset();
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window );
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Thread.
	bool isNull();
	bool isReady();
	void setThread();
	void prepare();
	
	// Borders.
	void setBorderX( float x );
	void setBorderY( float y );
};