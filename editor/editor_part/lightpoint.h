#pragma once

#include "own/sprite.h"
#include "own/text.h"
#include <vector>

struct LightPoint
{
	float x, y;
	float radius;
	float velocity;
	sf::Color color;
	std::vector <sf::Vector2f> points;
	
	LightPoint( float x = 0, float y = 0 );
	~LightPoint();
};

class LightPointVisible
{
	enum
	{
		COLOR  = 0,
		RADIUS,
		VEL,
		RADIUS_UNIT,
		VEL_UNIT,
		CURRENT,
		ARROW,
		AMOUNT
	};
	
	enum VALUES
	{
		COLOR_VALUE = 0,
		RADIUS_VALUE,
		VEL_VALUE,
		LINES,
		AMOUNT_VALUE
	};
	
	MySprite table;
	MySprite button;
	sf::RectangleShape rectColor;
	vector <MyText*> texts;
	vector <MyText*> texts_value;
	vector <string> valueStrs;
	vector <float> mins;
	vector <float> maxs;
	vector <bool> pressed;
	
	// Written.
	string written;
	float arrow_counter;
	float arrow_line;
	
	// States.
	int chosen;
	int active;
	
	// Specs.
	float type;
	float radius;
	float velocity;
	sf::Color color;
	vector <sf::Vector2f> points;
	
public:
	
	// Basics.
	LightPointVisible();
	~LightPointVisible();
	void free();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	// The other.
	void setType( int type );
	void setPosition( float x, float y );
	void setSpecs( float radius, float velocity, sf::Color color, vector <sf::Vector2f> points );
	
	// Getters.
	int getType();
	float getRadius();
	float getVelocity();
	sf::Color getColor();
	vector <sf::Vector2f> getPoints();
	
	bool isVisible();
	void clear();
	
private:
	
	sf::Color getColorFromText( string line );
	bool isPossibleCharColor( sf::Uint8 code );
	bool isPossibleChar( sf::Uint8 code );
	void setWritten();
};