#include "own/sprite.h"
#include "own/text.h"
#include "own/chunk.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <thread>

class Star
{
public:
	
	int silver;
	int gold;
	bool coin_medal;
	bool star_medal;
	bool x_medal;
	
	Star();
	~Star();
	void free();
};

class Worldtable
{
	float screen_w;
	float screen_h;
	string username;
	
	int ready;
	int chosen;
	MySprite button;
	vector <bool> locks;
	vector <float> xs;
	vector <float> ys;
	vector <MyText*> texts;
	
	thread* myThread;
	bool thread_ready;
	
	// In case of error.
	MySprite reloadButton;
	MyText information;
	
	// Reward.
	MySprite gold_star;
	MySprite silver_star;
	MySprite coin_medal;
	MySprite star_medal;
	MySprite x_medal;
	vector <Star*> stars;
	
	// Direction.
	MySprite left;
	MySprite right;
	
	// Sound.
	Chunk click;
	
public:
	
	// Basics.
	Worldtable();
	~Worldtable();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Getters.
	int isChosen();
	
	// Setters.
	void setThread();
	void setValues();
	void reload();
	void setUsername( string line );
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
};