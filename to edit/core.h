#pragma once

#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace std;

class Core
{
    int state;  // state of game
    bool open;
    unsigned FPS;

    int width;
    int height;

    sf::Event event;
    sf::Color color;
    sf::RenderWindow* window;

public:

    Core( int w, int h, int state, int FPS = 60 );
    ~Core();

    void free();
    bool load( string title = "" );

	sf::Event& getEvent();	// getter
    sf::RenderWindow*& getWindow();


    void clear();
    void display();

    void setVisible( const bool& visible );
    void setColor( const sf::Color& color );


    int& getState();    // get or set state, e.g. from intro to menu
    bool& isOpen();     // get or set open window


    const int& getWidth() const;
    const int& getHeight() const;
};
