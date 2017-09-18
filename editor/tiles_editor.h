#pragma once
#include "own/text.h"
#include "own/sprite.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include "hatchfoe.h"



class Tiles_editor
{
	// Basics.
	float screen_w;
	float screen_h;
	
	enum
	{
		TILE = 0,
		UNVISIBLE_TILE,
		OBJECT,
		COIN,
		FOE,
		AMOUNT
	};
	
	// Current block.
	int type;
	int chosen;
	float mouse_x;
	float mouse_y;
	
	// Hatch Foe Visible
	HatchFoeVisible hatchFoeVisible;
	
	MyText mouseInfo;
	sf::RectangleShape line;
	MySprite arrow;
	
	// Support.
	float width;
	bool grid;
	
	// Direction.
	float additional_x;
	float additional_y;
	
	// Drawable stuff.
	MySprite knight;
	MySprite coin;
	vector <MySprite*> tiles;
	vector <MySprite*> objects;
	vector <MySprite*> foes;
	
	// Main Major Vector.
	vector <Block> blocks;
	vector <HatchFoe> foeblocks;
	bool lastwasfoe;
	bool isrubbishon;
	
public:
	
	// Basics.
	Tiles_editor();
	~Tiles_editor();
	void free();
	void reset();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void drawTumbnails( sf::RenderWindow* &window );
	void drawLines( sf::RenderWindow* &window );
	
	void setRubbish( bool rubbish );
	void put();
	
	// Set.
	void setAdditionalX( float newX );
	void setAdditionalY( float newY );
	
	// Get.
	bool getGrid();
	string getType();
	string getChosen();
	
	// Streaming.
	void save( string path );
	void load( string path );
	
	// The rest.
	void griding();
	void clearVector();
	void deleteOne();
};