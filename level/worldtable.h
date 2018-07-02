#pragma once
#include "own/text.h"
#include "own/chunk.h"
#include "own/sprite.h"
#include "own/request.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>


struct Star
{
	int gold;
	int silver;
	bool x_medal;
	bool coin_medal;
	bool star_medal;
	
	Star();
	~Star();
	void free();
};

class Worldtable
{
	// Basics.
	float screen_w;
	float screen_h;
	string username;
	
	// Steer.
	MySprite left;
	MySprite right;
	
	// Sound and thread.
	Chunk click;
	MyThread thread;
	
	// In case of error.
	MyText information;
	MySprite reloadbutton;
	
	// Reward.
	MySprite gold_star;
	MySprite silver_star;
	MySprite x_medal;
	MySprite coin_medal;
	MySprite star_medal;
	vector <Star> stars;
	
	int ready;
	int chosen;
	MyText text_nr;
	MySprite sprite;
	vector <bool> locks;
	vector <sf::Vector2f> positions;
	
	
public:
	
	// Basics.
	Worldtable();
	~Worldtable();
	void free();
	void reset();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Getters.
	int isChosen();
	bool abletoreload();
	
	// Setters.
	void reload();
	void setThread();
	void setValues();
	void setUsername( string line );
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
};