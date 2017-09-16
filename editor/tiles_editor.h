#pragma once
#include "own/text.h"
#include "own/sprite.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

struct Block
{
	sf::Uint8 w;
	sf::Uint8 n;
	float x;
	float y;
	
	Block( sf::Uint8 w = 0, sf::Uint8 n = 0, float x = 0, float y = 0 );
	~Block();
};

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
	
	MyText mouseInfo;
	sf::RectangleShape line;
	MySprite arrow;
	
	// Support.
	float width;
	bool grid;
	
	// Additional information.
	MyText key_info;
	
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
	vector <Block> foeblocks;
	bool lastwasfoe;
	bool isrubbishon;
	
public:
	
	// Basics.
	Tiles_editor();
	~Tiles_editor();
	void free();
	void reset();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event, bool isRubbish );
	void draw( sf::RenderWindow* &window );
	void drawTumbnails( sf::RenderWindow* &window );
	void drawLines( sf::RenderWindow* &window );
	
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
	void griding( bool isRubbish );
	void clearVector();
	void deleteOne();
};