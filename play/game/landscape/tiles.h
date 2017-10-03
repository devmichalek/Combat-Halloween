#pragma once
#include "own/sprite.h"
#include "own/request.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class Tiles
{
	// Just for test.
	bool collision;
	sf::RectangleShape rect;
	
	// Basics.
	float screen_w;
	float screen_h;
	float border_x;
	float border_y;
	
	int width;
	float globalAlpha;
	
	vector <MySprite*> sprites;
	vector <vector <sf::Int8>> tiles;
	vector <vector <float>> alpha;
	
	// Thread stuff.
	string error;
	MyThread thread;
	
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
	
	// Keyboard - test.
	void turnCollision( bool collision );
	
	// Thread.
	bool isNull();
	bool isReady();
	void setThread( string message );
	void prepare( string message );
	string getError();
	
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