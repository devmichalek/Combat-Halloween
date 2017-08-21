#pragma once
#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <thread>

class Objects
{
	float screen_w;
	float screen_h;
	
	vector <MySprite*> sprites;
	vector <sf::Vector2f> fs;
	vector <int> types;
	
	// Thread stuff.
	std::thread* myThread;
	bool thread_ready;
	bool ready;
	
public:
	
	// Basics.
	Objects();
	~Objects();
	void free();
	
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Thread.
	bool isNull();
	bool isReady();
	void setThread();
	void setObjects();
};