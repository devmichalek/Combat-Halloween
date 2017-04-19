#pragma once

#include "platform/world/brick/block.h"
#include "SFML/Graphics.hpp"
#include "drawable/rect.h"
#include <vector>

using namespace std;

class Boulder_part
{
	double angle;
	double angle_vel;
	float vel;
	bool hit;
	
	sf::Uint8 alpha;
	int state;
	float startX;
	int startY;
	
	vector <Block*> blocks;
	
public:

	Boulder_part();
	~Boulder_part();
	void free();
	void reset( int distance );
	
	// Support.
	void addBlock( int n, int x, int y );
	
	void positioning( int width );
	void setPosition( int x, int y, float vel, double angle_vel );
	void moveX( float vel );
	void moving( Rect* rect, int width );
	
	// till 2
	unsigned getSize();
	float getX( unsigned which );
	float getY( unsigned which );
	int getNr( unsigned which );
	
	// only 3
	bool renderBoulder();
	float getBoulderX();
	float getBoulderY();
	double getBoulderAngle();
	sf::Uint8 getBoulderAlpha();
	void setBoulderAlpha( sf::Uint8 a );
		
	// other
	bool harm( int width );
};