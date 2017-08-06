#include "own/text.h"
#include "own/chunk.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <thread>

class Information
{
	float screen_w;
	float screen_h;
	
	MyText username;
	MyText money_form;
	MyText money;
	MyText earned_form;
	MyText earned;
	MyText logout;
	
	std::thread* myThread;
	bool thread_ready;
	bool open;
	
	// Sound.
	Chunk click;
	
public:
	
	// Basics.
	Information();
	~Information();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// The rest.
	void setThread();
	void saveUsername();
	bool close();
	void setMoney();
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
};