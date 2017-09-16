#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class Editor_details
{
	float screen_w;
	float screen_h;
	
	enum ARROWS
	{
		LEFT = 0,
		RIGHT,
		TOP,
		BOT,
		MIDDLE,
		AMOUNT
	};
	
	// Arrows.
	vector <MySprite*> arrows;
	float additional_x;
	float additional_y;
	
	// Grid.
	bool grid;
	MyText gridText;
	MyText gridStatusText;
	
	// Type and chosen.
	MyText typeText;
	MyText chosenText;
	
	// Name.
	int nameStatus;
	string nameStr;
	MyText nameForm;
	MyText name;
	float line;
	float counter;
	MyText arrow;
	MySprite table;
	MySprite agreebutton;
	
public:
	
	// Basics.
	Editor_details();
	~Editor_details();
	void free();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void drawName( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	// Getters.
	float getAdditionalX();
	float getAdditionalY();
	
	// Setters.
	void setGrid( bool grid );
	void setType( string type );
	void setChosen( string chosen );
	
	// Name.
	void setWritten();
	string getName();
	void setNameStatus( int nameStatus );
	int getNameStatus();
};