#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

struct Block
{
	sf::Uint8 w;
	sf::Uint8 n;
	float x;
	float y;
	
	Block( sf::Uint8 w = 0, sf::Uint8 n = 0, float x = 0, float y = 0 );
	~Block();
};

struct HatchFoe
{
	sf::Uint8 w;
	sf::Uint8 n;
	float x;
	float y;
	
	// Features.
	float armour;
	float damage;
	float velocity;
	float heartpoints;
	
	vector <string> texts;
	
	HatchFoe( sf::Uint8 w = 0, sf::Uint8 n = 0, float x = 0, float y = 0 );
	~HatchFoe();
};

class HatchFoeVisible
{
	enum Features
	{
		ARMOUR = 0,
		DAMAGE,
		VEL,
		HP,
		ADD_TEXT,
		AMOUNT
	};
	
	MySprite table;
	MySprite infobutton;
	MySprite plusbutton;
	MySprite minusbutton;
	MySprite doublebutton;
	
	vector <float> minimums;
	vector <float> maximums;
	vector <float> features;
	vector <bool> pluspressed;
	vector <bool> minuspressed;
	
	vector <MyText*> texts;
	vector <MyText*> formTexts;
	
	int type;
	bool visible;
	bool wasminus;
	float globalScaleY;
	
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
	void setFeatures( float a, float d, float v, float h );
	
	float getArmour();
	float getDamage();
	float getVelocity();
	float getHeartpoints();
};

class BalloonSetter
{
	
};