#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include "own/chunk.h"
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Chat
{
	// Basics.
	float screen_w;
	float screen_h;
	bool open;
	int capslock;
	int shift;
	bool used;
	bool black;
	
	// Background.
	MySprite background;
	MySprite second_background;
	MyText text_background;
	
	// Text written.
	vector <float> text_ys;
	vector <string> writtenStrs;
	MyText username;
	vector <MyText*> writtens;
	
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
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	// Getters.
	bool& isOpen();
	bool isUsed();
	char* getChar( int n );
	bool getCommand( string command );
	
	// The rest.
	void setUsername( string line );
	void setWritten();
	void setBlack( bool black = false );
};