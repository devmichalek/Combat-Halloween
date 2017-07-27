#include "own/chunk.h"
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Pausesystem
{
	MySprite blackout;
	MyText text;
	
	bool active;
	bool changed;
	bool release;
	
	// Sound.
	Chunk click;
	bool playable;
	
public:
	
	// Basics.
	Pausesystem();
	~Pausesystem();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window, double elapsedTime );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Rest.
	bool isActive();
	void setActive( bool active );
	bool isChanged();
	void setChanged( bool changed );
	int getAlpha();
	
	// Sound.
	void setPlayable( bool playable = true );
	void setVolume( float volume = 50 );
};