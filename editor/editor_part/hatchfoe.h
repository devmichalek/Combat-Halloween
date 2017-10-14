#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "play/game/foe/balloonchat.h"
#include <vector>

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
	float scale;
	
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
		SCALE,
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
	
	// Comments.
	int commentState;
	int which;
	MyText arrow;
	MyText oneOf;
	float arrowLine;
	float arrowCounter;
	MySprite addCommentButton;
	MySprite deleteCommentButton;
	MySprite nextCommentButton;
	MySprite backCommentButton;
	vector <string> commentsStr;
	Balloonchat balloonchat;
	
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
	void mechanics( double elapsedTime );
	
	bool& isVisible();
	void clear();
	int getType();
	void setType( int type );
	void setPosition( float x, float y );
	void setFeatures( float a, float d, float v, float h, float s );
	void setComments( vector <string> newComments );
	
	void setFoeSize( float width, float height );
	void setFoePosition( float foe_x, float foe_y );
	
	float getArmour();
	float getDamage();
	float getVelocity();
	float getHeartpoints();
	float getScale();
	float getX();
	float getY();
	vector <string> getComments();
	
private:
	
	void setUpComments();
	void setBalloonChat();
	void setCommentPosition();
	void deleteSpaces( string &line );
};