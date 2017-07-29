#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "own/chunk.h"

class Button
{
	MySprite button;
	bool locked;
	bool pressed;
	
	// Sound.
	Chunk click;
	bool playable;
	
public:
	
	// Basics.
	Button();
	~Button();
	void free();
	
	void load( float x, float y, string path, bool locked = false );
	void setScale( float x, float y );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Getters.
	bool isPressed();
	float getBot();
	
	// Sound.
	void setPlayable( bool playable = true );
	void setVolume( float volume = 50 );
};