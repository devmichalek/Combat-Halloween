/**
    core.h
    Purpose: class Core responsible for sending renderer, accessing start valuables etc.

    @author Adrian Michalek
    @version 2016.08.19
	@email adrmic98@gmail.com
*/

#pragma once

#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace std;

class Core
{
    int state;  // state of game
    bool open;
    // unsigned FPS;

    unsigned width;
    unsigned height;
	
	unsigned min_width, max_width;
	unsigned min_height, max_height;

    sf::Event event;
    sf::Color color;
    sf::RenderWindow* window;

public:

    Core( unsigned w, unsigned h, int state/*, int FPS = 60*/ );
    ~Core();

    void free();
    bool load( string title = "" );

	sf::Event& getEvent();	// getter
    sf::RenderWindow*& getWindow();


    void clear();
    void display();
	
	bool setView();
    void setVisible( const bool& visible );
    void setColor( const sf::Color& color );


    int& getState();    // get or set state, e.g. from intro to menu
    bool& isOpen();     // get or set open window


    const unsigned getWidth() const;
    const unsigned getHeight() const;
	int getX() const;
	int getY() const;
	float getXScale() const;
	float getYScale() const;
};
