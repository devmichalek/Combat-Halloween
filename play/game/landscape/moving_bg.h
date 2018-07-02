#pragma once
#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class Moving_bg
{
	int type;
	float screen_w;
	float screen_h;
	float velocity;
	
	vector <int> types;
	vector <sf::Vector2f> fs;
	vector <MySprite*> sprites;

public:

	Moving_bg();
	~Moving_bg();
	void free();
	
	void load( float screen_w, float screen_h, int type );
	void draw( sf::RenderWindow* &window, sf::Shader &shader );
	void mechanics( double elapsedTime, float direction );
};