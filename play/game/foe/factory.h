#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include "skeleton.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML/Graphics/RectangleShape.hpp"
#include <vector>
#include <thread>

template <typename F>
class Factory
{
	// Foe table.
	MySprite foebar;
	MySprite foetable;
	
	// Just for test.
	bool collision;
	sf::RectangleShape rectcollisionwalk;
	sf::RectangleShape rectcollisionattack;
	
	// Basics.
	int type;
	string name;
	
	float screen_w;
	float screen_h;
	float border_x;
	float border_y;
	
	// Thread stuff.
	std::thread* myThread;
	bool thread_ready;
	bool ready;
	
	vector <F*> foes;
	vector <sf::Uint8> lines;
	vector <MySprite*> sprites;
	
public:
	
	Factory();
	~Factory();
	void free();
	void reset();
	void load( float screen_w, float screen_h, int type, string name );
	void draw( sf::RenderWindow* &window );
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	void mechanics( double elapsedTime );
	
	// Keyboard.
	void turnCollision( bool collision );
	bool getCollision();
	
	// Thread.
	bool isNull();
	bool isReady();
	void setThread();
	void prepare();
	void positioning( vector <sf::Vector2f> fs, vector <sf::Uint8> types );
	
	// Borders.
	void setBorderX( float x );
	void setBorderY( float y );
	
	// Check collision and activities.
	void harm( sf::Rect <float> rect, float damage ); 	// check if foe is harmed
	bool isHarmed( sf::Rect <float> rect );	// return true if knight is harmed
	void walk( sf::Rect <float> rect, double elapsedTime );
};