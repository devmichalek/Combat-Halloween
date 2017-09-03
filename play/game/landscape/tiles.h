#pragma once
#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <thread>

class Tiles
{
	// Basics.
	float screen_w;
	float screen_h;
	float border_x;
	float border_y;
	bool fadingout;
	
	// Visible tiles.
	vector <MySprite*> sprites;
	vector <sf::Vector2f> fs;
	vector <sf::Uint8> types;
	
	// Unvisible tiles.
	vector <sf::Vector2f> ufs;
	vector <sf::Uint8> utypes;
	vector <float> ualpha;
	
	// Thread stuff.
	std::thread* myThread;
	bool thread_ready;
	bool ready;
	
public:
	
	// Basics.
	Tiles();
	~Tiles();
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
	
	// Check collision.
	bool checkCollisionRect( sf::Rect <float> rect );
	void tickGravity( sf::Rect <float> rect, double elapsedTime );
	
	// Borders.
	void setBorderX( float x );
	void setBorderY( float y );
	float getBorderX();
	float getBorderY();
	float getScreenWidth();
	float getScreenHeight();
};