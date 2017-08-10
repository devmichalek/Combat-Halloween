#include "menu/circlebutton.h"
#include "menu/volume_button.h"
#include "menu/pausesystem.h"
#include "own/music.h"

class Play
{
	// Basics.
	bool menu;
	bool level;
	bool table;
	bool run;
	
	// Objects.
	MySprite background;
	Circlebutton homebutton;
	Circlebutton levelbutton;
	Circlebutton chunkbutton;
	Circlebutton musicbutton;
	Volume_button chunk_volume;
	Volume_button music_volume;
	Pausesystem pausesystem;
	Music music;
	
public:
	
	// Basics.
	Play();
	~Play();
	void free();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void head( sf::RenderWindow* &window, double elapsedTime );
	
	// Support.
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	void fades( double elapsedTime );
	
	// Sound.
	void loadSound();
	void saveSound();
	
	// Getters.
	bool isMenu();
	bool isLevel();
	bool isTable();
};