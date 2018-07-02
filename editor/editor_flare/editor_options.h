#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class Editor_options
{
	// Basics.
	float screen_w;
	float screen_h;
	int status;
	
	enum
	{
		KEYBOARD = 0,
		KEY_A,
		KEY_S,
		KEY_D,
		KEY_Z,
		KEY_X,
		KEY_C,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_TOP,
		KEY_BOT,
		KEY_ENTER,
		KEY_ESC,
		KEY_CTRL,
		KEY_SPACE,
		MOUSE,
		MOUSE_LEFT,
		MOUSE_RIGHT,
		MOUSE_SCROLL,
		AMOUNT
	};
	
	MyText orText;
	MyText deleteText;
	
	vector <MyText*> texts;
	vector <MyText*> texts2;
	MySprite table;
	MySprite closebutton;
	sf::RectangleShape line;
	
public:
	
	// Basics.
	Editor_options();
	~Editor_options();
	void free();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	// The other.
	void setStatus( int status );
	int getStatus();
};