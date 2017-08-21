#include "own/sprite.h"
#include "own/text.h"
#include "own/chunk.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <vector>
#include <thread>

class Knight_specs
{
	float screen_w;
	float screen_h;
	string username;
	
	enum PARTS
	{
		HELMET = 0,
		BODY,
		SHIELD,
		SWORD,
		BOOTS,
		AMOUNT
	};
	
	
	// Table stuff.
	MySprite left_arrow;
	MySprite table;
	MySprite gear_top, gear_bot;
	float moving_state;
	float x1, x2;
	float x, y;
	
	// The rest.
	MySprite knight;
	vector <MySprite*> parts;
	vector <sf::Vector2f*> rects;
	std::thread* myThread;
	bool thread_ready;
	bool ready;
	
	int chosen;
	int lastChosen;
	
	float offset;
	float line;
	
	enum VARIABLES
	{
		LEVEL = 0,
		ARMOUR,
		HEALTH,
		DAMAGE,
		SPEED,
		VARIABLES_AMOUNT
	};
	
	// View, specs
	sf::View view;
	vector <MyText*> categories;
	vector <MyText*> values;
	float text_x;
	
	// Sound.
	Chunk click;
	
public:
	
	// Basics.
	Knight_specs();
	~Knight_specs();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// The rest.
	void setThread();
	void setValues();
	bool isReady();
	void reload();
	void setUsername( string line );
	void setChosen( int n );
	bool isChosen();
	
	// Values.
	void moveValues( float x = 0 );
	void setPositionValues( float x = 0 );
	void reloadValues();
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
};