#pragma once

#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace sf;
using namespace std;

class Core
{
    int state;  // state of game
    bool open;
    unsigned FPS;

    unsigned width;
    unsigned height;

    Event event;
    Color color;
    RenderWindow* window;

public:

    Core( unsigned width = 0, unsigned height = 0, unsigned FPS = 60 );
    ~Core();

    void free();
    bool load( string title = "" );

    Event& getEvent();
    RenderWindow*& getWindow();


    void clear();
    void display();

    void setVisible( bool visible );
    void setColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );


    int& getState();    // get or set state, e.g. from intro to menu
    bool& isOpen();     // get or set open window


    unsigned getWidth();
    unsigned getHeight();
};
