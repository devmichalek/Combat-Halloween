#include "own/sprite.h"
#include "own/text.h"
#include "own/chunk.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <thread>

class Worldtable
{
	float screen_w;
	float screen_h;
	
	bool ready;
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
	bool isChosen();
	string getName();
	
	// Setters.
	void setThread();
	void setValues();
	void reload();
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
};