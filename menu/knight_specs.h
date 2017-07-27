#include "own/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
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
	
	MySprite animation;
	vector <MySprite*> parts;
	vector <MySprite*> blocks;
	
	int chosen;
	int lastChosen;
	float x, y;
	
	float offset;
	float line;
	
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
};