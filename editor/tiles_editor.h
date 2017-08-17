#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class Tiles_editor
{
	float screen_w;
	float screen_h;
	
	MyText info;
	MySprite bg;
	MySprite coin;
	MySprite savebutton;
	MySprite loadbutton;
	sf::RectangleShape line;
	
	int which;
	int chosen;
	float mouse_x, mouse_y;
	bool grid;
	int width;
	vector <MySprite*> tiles;
	vector <MySprite*> objects;
	vector <MySprite*> foes;
	
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
	
	void save();
	void load();
};