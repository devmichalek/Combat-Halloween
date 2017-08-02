#include "own/sprite.h"
#include "own/text.h"
#include "own/chunk.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <vector>

class Knight_specs
{
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
	MySprite table;
	MySprite gear_top, gear_bot;
	float moving_state;
	float x1, x2;
	float x, y;
	
	// The rest.
	MySprite knight;
	vector <MySprite*> parts;
	vector <sf::Vector2f*> rects;
	
	int chosen;
	int lastChosen;
	
	float offset;
	float line;
	
	// View, specs
	sf::View view;
	vector <MyText*> categories;
	vector <MyText*> values;
	
	// Sound.
	Chunk click;
	bool playable;
	
public:
	
	Knight_specs();
	~Knight_specs();
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