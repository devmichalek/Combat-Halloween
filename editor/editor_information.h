#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Editor_information
{
	MySprite layout;
	MySprite table;
	MySprite agreeButton;
	MySprite disagreeButton;
	MyText info;
	MyText worldname;
	
	int status;
	
public:
	
	// Basics.
	Editor_information();
	~Editor_information();
	void free();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void drawLayout( sf::RenderWindow* &window, bool permit = false );
	
	// Set info and worldname.
	void setInfo( string line );
	void setWorldname( string line );
	void setAsVisible();
	bool isActive();
	bool answerYes();
	bool answerNo();
};