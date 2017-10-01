#pragma once

#include <SFML/Graphics.hpp>
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
/*
class LightPointVisible
{
	enum Features
	{
		RADIUS = 0,
		VEL,
		AMOUNT
	};
	
	MySprite table;
	MySprite infobutton;
	MySprite plusbutton;
	MySprite minusbutton;
	MySprite doublebutton;
	
	vector <float> minimums;
	vector <float> maximums;
	vector <float> values;
	vector <bool> pluspressed;
	vector <bool> minuspressed;
	
	vector <MyText*> texts;
	vector <MyText*> formTexts;
	
	int type;
	bool visible;
	bool wasminus;
	float globalScaleY;
	
	// For scale calculations.
	float foe_x, foe_y;
	float width;
	float height;
	
public:
	
	HatchFoeVisible();
	~HatchFoeVisible();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	bool isVisible();
	void clear();
	int getType();
	void setType( int type );
	void setPosition( float x, float y );
	void setFeatures( float a, float d, float v, float h, float s );
	
	void setFoeSize( float width, float height );
	void setFoePosition( float foe_x, float foe_y );
	
	float getArmour();
	float getDamage();
	float getVelocity();
	float getHeartpoints();
	float getScale();
	float getX();
	float getY();
};*/