#pragma once
#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <thread>

class Knight
{
	enum Keys
	{
		LEFT_K = 0,
		RIGHT_K,
		JUMP_K,
		ATTACK_K,
		AMOUNT_K
	};
	vector <int> keys;
	
	
	enum Activity
	{
		IDLE = 0,
		WALK,
		RUN,
		JUMP,
		ATTACK,
		JUMP_ATTACK,
		DEAD,
		AMOUNT
	};
	int line;
	int which;
	float offset;
	vector <MySprite*> sprites;
	
	vector <float> x1s;
	vector <float> x2s;
	
	// Steer.
	bool right;
	sf::Uint8 flip;
	sf::Uint8 moving;
	
	// Features.
	string username;
	float armour;
	float damage;
	float velocity;
	float heartpoints;
	
	
	// Activity variables.
	float running;
	float running_line;
	
	float jumping;
	int jumping_line;
	
	
	// Thread.
	std::thread* myThread;
	bool thread_ready;
	bool ready;
	
public:
	
	// Basics.
	Knight();
	~Knight();
	void free();
	
	void load( float screen_w, float screen_h );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	
	// Hero.
	void setMoving( sf::Uint8 moving );
	void moveX( float x = 0 );
	void flipSprites();
	
	
	// Thread.
	bool isNull();
	bool isReady();
	void setThread();
	void setFeatures();
	
	// Sound and username.
	void setUsername( string line );
	
	
	// The rest.
	float getX();
	float getY();
	float getVelocity();
};