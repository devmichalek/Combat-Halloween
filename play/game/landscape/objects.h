#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <thread>

class Objects
{
	// Test - FPS.
	sf::Clock clock;
	float currentTime;
	bool FPS_state;
	MyText FPS;
	float counter;
	float line;
	
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
	void drawFPS( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// FPS.
	void setFPS( bool state );
	bool getFPS();
	
	// Thread.
	bool isNull();
	bool isReady();
	void setThread();
	void prepare();
	
	// Borders.
	void setBorderX( float x );
	void setBorderY( float y );
};