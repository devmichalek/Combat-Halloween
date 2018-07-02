<<<<<<< HEAD
/**
    level.h
    Purpose: class Level - huge object which contains stuff drawable in level state.

    @author Adrian Michalek
    @version 2016.12.20
	@email adrmic98@gmail.com
*/

#pragma once

#include "sound/sound.h"
#include "sound/music.h"
#include "choice/backtomenu.h"
#include "choice/choice.h"
#include "character/character.h"
#include "cube/cube.h"
#include "cube/difficulty.h"
#include "bonus_choice/bonus_choice.h"

class Level
{
	int state;
	int screen_w, screen_h;
	
	// level menu objects
	Sound sound;
	MySprite* background;
	Music* music;
	Backtomenu* backtomenu;
	Choice* choice;
	Character* character;
	Cube* cube;
	Difficulty* difficulty;
	Bonus_choice* bonus_choice;
	
public:

	Level();
    ~Level();
    void free();
	
    void load( unsigned screen_w, unsigned screen_h );
	void loadCharacter();
	void loadWorlds();
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	void setSound();
	bool isQuit();
	bool nextState();
	bool backToMenu();
	void reset();
	void reloadMusic();
	
	
	int getWorld();
	int getBonus_world();
	int getCharacter();
	int getWorldsize();
	int getFlatness();
	int getDifficulty();
=======
#pragma once
#include "worldtable.h"
#include "menu/circlebutton.h"
#include "menu/volume_button.h"
#include "level/chat.h"
#include "menu/pausesystem.h"
#include "own/music.h"

class Level
{
	// Basics.
	bool back;
	bool next;
	bool run;
	
	// Objects.
	MySprite background;
	Worldtable worldtable;
	Circlebutton homebutton;
	Circlebutton playbutton;
	Circlebutton updatebutton;
	Circlebutton chunkbutton;
	Circlebutton musicbutton;
	Volume_button chunk_volume;
	Volume_button music_volume;
	Chat chat;
	Pausesystem pausesystem;
	Music music;
	
public:
	
	// Basics.
	Level();
	~Level();
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
	bool isNext();
	bool isBack();
>>>>>>> Combat-Halloween/master
};