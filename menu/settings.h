#include "own/sprite.h"
#include "own/text.h"
#include "own/chunk.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

class Settings
{
	enum activity
	{
		MOVE_LEFT = 0,
		MOVE_RIGHT,
		JUMP,
		ATTACK,
		JUMP_ATTACK
	};
	
	vector <MyText*> state_texts;
	vector <MyText*> active_texts;
	MyText contactme;
	
	// Table.
	MySprite table;
	MySprite gear_top;
	MySprite gear_bot;
	float moving;
	float x1, x2;
	
public:

	// Basics.
	Settings();
	~Settings();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Sound.
	void setPlayable( bool playable = true );
	void setVolume( float volume = 50 );
};