#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Chat
{
	sf::Color commandColor;
	sf::Color typicalColor;
	
	// Animation.
	float globalYScale;
	float globalYLine;
	
	// Basics.
	float screen_w;
	float screen_h;
	float scale_x;
	float scale_y;
	
	// The rest basics.
	bool open;
	bool used;
	
	// Background.
	MyText escButton;
	MySprite background;
	
	// Text written.
	MyText username;
	vector <MyText*> writtens;
	vector <string> writtenStrs;
	
	// Arrow.
	float line;
	float counter;
	MyText arrow;
	
public:
	
	// Basics.
	Chat();
	~Chat();
	void free();
	void reset();
	
	void load( float screen_w, float screen_h, bool white = false );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	void fadeout( float v = 1, int min = 0 );
	
	// Getters.
	bool& isOpen();
	bool isCommand();
	bool findCommand( string line );
	
	// The rest.
	void setUsername( string line );
	void setWritten();
	void setError();	// Can't find command.
	
	// Set Colors.
	void setCommandColor( sf::Color newColor );
	void setTypicalColor( sf::Color newColor );
};