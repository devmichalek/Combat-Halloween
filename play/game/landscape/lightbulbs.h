#pragma once
#include "own/sprite.h"
#include "own/request.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

struct LightBulbPoint
{
	float x, y;
	float xS, yS;
	float radius;
	float velocity;
	sf::Glsl::Vec4 color;
	std::vector <sf::Vector2f> points;
	
	int state;
	bool direction;
	
	LightBulbPoint( float x = 0, float y = 0 );
	~LightBulbPoint();
	void calculate( double elapsedTime );
	bool isVisible( float bx, float by, float screen_w, float screen_h );
};

class LightBulbs
{
	// Basics.
	float screen_w;
	float screen_h;
	float border_x;
	float border_y;
	
	// Shader and shader calculation.
	
	float alpha;
	int arraySize;
	sf::Shader shader;
	sf::Clock clock;
	sf::Time frameTime, time;
	
	// Light points.
	vector <float> radii;
	vector <sf::Glsl::Vec4> colors;
	vector <sf::Glsl::Vec2> positions;
	vector <LightBulbPoint> lightBulbPoints;
	
	// Thread stuff.
	string error;
	MyThread thread;
	MyThread threadShader;
	
public:
	
	// Basics.
	LightBulbs();
	~LightBulbs();
	void free();
	void reset();
	void load( float screen_w, float screen_h );
	void mechanics( double elapsedTime );
	void calculation( double elapsedTime );
	void setAlpha( float alpha );
	
	// Thread.
	bool isNull();
	bool isReady();
	void setThread( string message );
	void prepare( string message );
	string getError();
	
	// Borders.
	void setBorderX( float x );
	void setBorderY( float y );
	
	// Getters.
	sf::Shader& getShader();
};