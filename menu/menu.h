#include "knight_specs.h"
#include "link_button.h"
#include "button.h"
#include "circlebutton.h"
#include "settings.h"
#include "volume_button.h"
#include "information.h"
#include "level/chat.h"
#include "pausesystem.h"
#include "own/music.h"

class Menu
{
	// Basics.
	bool ready;
	bool close;
	bool run;
	
	// Objects.
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
	Circlebutton reloadbutton;
	Circlebutton settingsbutton;
	Settings settings;
	Volume_button chunk_volume;
	Volume_button music_volume;
	Information information;
	Chat chat;
	Pausesystem pausesystem;
	Music music;
	
public:
	
	// Basics.
	Menu();
	~Menu();
	void free();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void head( sf::RenderWindow* &window, double elapsedTime );
	
	// Support.
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	void fades( double elapsedTime );
	
	// Sound and username.
	void setUsername( string line );
	void loadSound();
	void saveSound();
	
	// Getters.
	bool isReady();
	bool isClose();
};