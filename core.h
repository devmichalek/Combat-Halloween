#pragma once
#define _GLIBCXX_USE_CXX11_ABI 0
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Core {

	int width;
    int height;
	
	int state;  // state of the game
    bool open;	// if window is still open

    sf::Event event;
    sf::Color color;
    sf::RenderWindow* window;
	sf::Clock clock;
	
public:

	Core( int state );
    ~Core();
	
    void free();
    bool set( std::string title = "", int style = sf::Style::Titlebar | sf::Style::Close );

	sf::Event& getEvent();	// getter
    sf::RenderWindow*& getWindow();

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