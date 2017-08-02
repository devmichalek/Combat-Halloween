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
	
public:
	
	// Basics.
	Circlebutton();
	~Circlebutton();
	void free();
	
	void load( string path, bool active = false );
	void setPosition( float x, float y, float x_scale, float y_scale );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	void fadein( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	
	// Getters and setters.
	bool isActive();
	void setActive( bool active );
	void changeActive();

	bool isChanged();
	void setChanged( bool changed );
	
	float getLeft();
	float getRight();
	float getBot();
	
	// Sound.
	void setPlayable( bool playable );
	void setVolume( float volume );
};