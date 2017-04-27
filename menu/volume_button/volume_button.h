/**
    volume_button.h
    Purpose: class Volume_button - to show set volume (music, chunk), to show bar.

    @author Adrian Michalek
    @version 2016.10.21
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "menu/click.h"

class Volume_button :public Click
{
	// name is "chunk" or "music"
	MyText name;

	// show percent
	MyText percent;
	
	// sprites
	MySprite plus;
	MySprite minus;
	
	sf::Uint8 max;	// max volume
	sf::Uint8 volume;
	sf::Uint8 last_volume;
	
	// hover
	bool plus_focus;
	bool minus_focus;
	float scale;
	int y_state;
	
public:
	
	// Basics.
	Volume_button( float volume = 1 );
	~Volume_button();
	void free();
	
	void load( int y, string new_name );
	void draw( sf::RenderWindow* &window );
	void handle( sf::Event &event, int r_x, int r_y );
	
	void fadein( int i = 1, int max = 255 );
	void fadeout( int i = 1, int min = 0 );
	
	// Extra
	int getBot();
	int getRight();
	
	bool isChanged();
	sf::Uint8 getVolume();
	
	// Window.
	void setScale( float s_x, float s_y );
	void setView( int w, int r_x, int r_y );
};