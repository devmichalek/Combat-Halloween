#pragma once
#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

class Tiles_editor
{
	float screen_w;
	float screen_h;
	
	MySprite bg;
	MySprite knight;
	
	int which;
	int chosen;
	float mouse_x, mouse_y;
	bool grid;
	int width;
	vector <MySprite*> tiles;
	
	vector <int> ws;	// which
	vector <int> ns;	// chosen
	vector <float> xs;	// x position
	vector <float> ys;	// y position
	
	
public:
	
	Tiles_editor();
	~Tiles_editor();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
};