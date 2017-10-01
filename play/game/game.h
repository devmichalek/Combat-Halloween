#pragma once
#include "play/game/landscape/moving_bg.h"
#include "play/game/landscape/tiles.h"
#include "play/game/landscape/objects.h"
#include "play/game/landscape/coins.h"
#include "play/game/knight/knight.h"
#include "play/game/knight/eye.h"
#include "play/game/foe/factory.h"
#include "play/game/foe/skeleton.h"
#include "play/game/foe/zombie.h"

class Game
{
	// Basics.
	bool table;
	bool loaded;
	float alpha;
	string message;
	
	// Objects.
	Moving_bg moving_bg;
	Knight knight;
	Eye eye;
	Tiles tiles;
	Objects objects;
	Coins coins;
	Factory <Skeleton> skeletons;
	Factory <Zombie> zombies;
	
public:
	
	// Basics.
	Game();
	~Game();
	void free();
	void reset();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Sound and username.
	void setMessage( string message );
	void setUsername( string line );
	void setPlayable( bool playable );
	void setVolume( float volume );
	
	// Getters.
	bool isTable();
	float getAlpha();
	
	// Loading.
	void loading( int which );
	int getStatus();
	void resetStatus();
	string getLoadingError();
	
	// In addition for test reasons.
	void turnCollision( bool collision );
	bool getCollision();
	void turnFPS( bool fps );
	bool getFPS();
	void commitSuicide();
};