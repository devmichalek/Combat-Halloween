#pragma once
#include "own/text.h"
#include "own/chunk.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <thread>

class Information
{
	float screen_w;
	float screen_h;
	string username_str;
	
	MyText username;
	MyText money_form;
	MyText money;
	
	std::thread* myThread;
	bool thread_ready;
	bool ready;
	
public:
	
	// Basics.
	Information();
	~Information();
	void free();
	
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// The rest.
	void setUsername( string line );
	void setThread();
	void setMoney();
	bool isReady();
};