#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "own/chunk.h"

class Circlebutton
{
	MySprite button;
	bool active;
	bool changed;
	
	// Sound.
	Chunk click;
	bool playable;
	
public:
	
	// Basics.
	Circlebutton();
	~Circlebutton();
	void free();
	
	void load( string path, bool active = false );
	void set( float x, float y, float x_scale, float y_scale );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window, double elapsedTime );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Getters.
	bool isActive();
	void setActive( bool active );
	void changeActive();
	float getLeft();
	bool isChanged();
	void setChanged( bool changed );
	
	// Sound.
	void setPlayable( bool playable = true );
	void setVolume( float volume = 50 );
};