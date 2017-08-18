#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class Tiles_editor
{
	enum
	{
		COIN = 0,
		TILE,
		OBJECT,
		FOE,
		AMOUNT
	};
	
	// Support.
	float screen_w;
	float screen_h;
	
	// Temporary.
	int width;
	bool grid;
	int which;
	int chosen;
	float mouse_x;
	float mouse_y;
	MyText info;
	MyText key_info;
	
	// Drawable stuff.
	MySprite coin;
	vector <MySprite*> tiles;
	vector <MySprite*> objects;
	vector <MySprite*> foes;
	sf::RectangleShape line;
	
	// Vectors.
	vector <int> ws;	// which
	vector <int> ns;	// chosen
	vector <float> xs;	// x position
	vector <float> ys;	// y position
	
public:
	
	// Basics.
	Tiles_editor();
	~Tiles_editor();
	void free();
	void reset();
	void clear();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event, bool isRubbish );
	void draw( sf::RenderWindow* &window );
	
	// In addition.
	void save( string path );
	void load( string path );
};