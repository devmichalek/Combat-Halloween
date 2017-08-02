#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "own/chunk.h"

class Link_button
{
	MySprite button;
	string url;
	
	// Sound.
	Chunk click;
	
public:

	// Basics.
	Link_button();
	~Link_button();
	void free();
	
	void load( float x, float y, string path );
	void setScale( float x, float y );
	void setUrl( string url );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Getters.
	float getRight();
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
};