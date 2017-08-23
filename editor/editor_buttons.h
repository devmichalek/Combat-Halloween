#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Editor_buttons
{
	// Basics.
	float screen_w;
	float screen_h;
	
	bool saveState;
	bool loadState;
	bool released;
	bool focus;
	string path;
	
	MySprite savebutton;
	MySprite loadbutton;
	MyText saveText;
	MyText loadText;
	MyText rubbishTextdelete;
	MyText rubbishTextmode;
	
	MyText form;
	MyText info;
	
public:
	
	// Basics.
	Editor_buttons();
	~Editor_buttons();
	void free();
	void reset();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	// Getters.
	bool isSave();
	bool isLoad();
	bool isFocus();
	string getPath();
	
	// Setters.
	void setSave();
	void setLoad();
	void setFocus( bool f );
	
	// Support.
	bool isPossibleKey( sf::Event &event );
	string getName( int n );
	void organizeWritten();
	void setColorWritten();
};