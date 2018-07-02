<<<<<<< HEAD
/**
    core.h
    Purpose: class Core responsible for sending renderer, accessing start valuables etc.

    @author Adrian Michalek
    @version 2016.08.19
	@email adrmic98@gmail.com
*/

#pragma once

=======
#pragma once
#define _GLIBCXX_USE_CXX11_ABI 0
>>>>>>> Combat-Halloween/master
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

<<<<<<< HEAD
using namespace std;

class Core
{
    int state;  // state of game
    bool open;

    unsigned width;
    unsigned height;
=======
class Core {

	int width;
    int height;
	
	int state;  // state of the game
    bool open;	// if window is still open
>>>>>>> Combat-Halloween/master

    sf::Event event;
    sf::Color color;
    sf::RenderWindow* window;
<<<<<<< HEAD

public:

    Core( unsigned w, unsigned h, int state );
    ~Core();

    void free();
    bool load( string title = "" );
=======
	sf::Clock clock;
	
public:

	Core( int state );
    ~Core();
	
    void free();
    bool set( std::string title = "", int style = sf::Style::Titlebar | sf::Style::Close );
>>>>>>> Combat-Halloween/master

	sf::Event& getEvent();	// getter
    sf::RenderWindow*& getWindow();

<<<<<<< HEAD

    void clear();
    void display();
	
    void setVisible( const bool& visible );
    void setColor( const sf::Color& color );


    int& getState();    // get or set state, e.g. from intro to menu
    bool& isOpen();     // get or set open window


    const unsigned getWidth() const;
    const unsigned getHeight() const;
};
=======
    void clear();
    void display();
	
	void setView( sf::View view );
	void resetView();
	
    void setVisible( const bool& visible );
    void setColor( const sf::Color& color );

    int& getState();    // get or set state, e.g. from intro to menu
    bool& isOpen();     // get or set open window

    const int& getWidth() const;
    const int& getHeight() const;
	const double getElapsedTime();
};
>>>>>>> Combat-Halloween/master
