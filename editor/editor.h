#pragma once
#include "menu/circlebutton.h"
#include "editor_buttons.h"
#include "editor_information.h"
#include "editor_details.h"
#include "editor_options.h"
#include "tiles_editor.h"
#include "level/chat.h"

class Editor
{
	// Basics.
	bool back;
	bool play;
	
	// Objects.
	MySprite background;
	Editor_buttons editor_buttons;
	Editor_information editor_information;
	Editor_details editor_details;
	Editor_options editor_options;
	Tiles_editor tiles_editor;
	Chat chat;
	
public:
	
	// Basics.
	Editor();
	~Editor();
	void free();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void head( sf::RenderWindow* &window, double elapsedTime );
	
	// Support.
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	// Set username.
	void setUsername( string line );
	
	// Getters.
	bool isBack();
	bool isPlay();
};