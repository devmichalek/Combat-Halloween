#pragma once
#include "own/text.h"
#include "own/sprite.h"
#include "own/request.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

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
	string error;
	MyThread thread;
	
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
	void setThread( string message );
	void prepare( string message );
	string getError();
	
	// Borders.
	void setBorderX( float x );
	void setBorderY( float y );
};