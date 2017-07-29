#include "knight_specs.h"
#include "link_button.h"
#include "button.h"
#include "circlebutton.h"
#include "settings.h"
#include "pausesystem.h"
#include "own/music.h"

class Menu
{
	bool ready;
	bool close;
	MySprite background;
	Knight_specs knight_specs;
	Link_button github;
	Link_button scores;
	Link_button website;
	Button singleplayer;
	Button multiplayer;
	Button exit;
	Circlebutton chunkbutton;
	Circlebutton musicbutton;
	Circlebutton settingsbutton;
	Settings settings;
	Pausesystem pausesystem;
	Music music;
	
public:
	
	Menu();
	~Menu();
	void free();
	
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window, double elapsedTime );
	
	bool isReady();
	bool isClose();
};