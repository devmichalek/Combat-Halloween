/**
    kunai.h
    Purpose: class Kunai to contain textures, throw kunai, contains 5 kunai.

    @author Adrian Michalek
    @version 2016.12.15
	@email adrmic98@gmail.com
*/

#pragma once

#include <stack>
#include "kunai_bit.h"
#include "kunai_effects.h"

class Kunai
{
	float vel;
	float scale;
	
	vector <float> damage;
	vector <Kunai_bit*> bits;
	vector <MySprite*> sprites;
	Kunai_effects kunai_effects;
	
public:
	
	Kunai();
	~Kunai();
	void free();
	void load();
	void draw( sf::RenderWindow* &window );
	void drawEffects( sf::RenderWindow* &window  );
	void mechanics();
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	unsigned getSize();
	bool isActive( int which );
	int getX( int which );
	int getW( int which );
	Rect* getRect( int which );
	Rect* getEffectRect( int which );
	float getDamage( int which );
	bool isHealKunai( int which );
	bool isExplosiveKunai( int which );
	bool isStuntKunai( int which );

	void destroy( int which );
	void throwed( int x, int y, bool right, int which );
	
	// In action
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void setColor( sf::Color color );
	
	// Sound stuff.
	void turn();
	void turnOn();
	void turnOff();
	void setVolume( int v );
};