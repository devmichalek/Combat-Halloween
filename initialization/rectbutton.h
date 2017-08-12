#pragma once
#include "own/text.h"
#include "SFML/Graphics/Rectangleshape.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

class Rectbutton
{
	float alpha;
	float alphaBorders;
	
	bool focus;
	bool clicked;
	sf::Uint8 state;
	
	MyText text_one;
	MyText text_two;
	vector <sf::RectangleShape*> rects;
	
public:
	
	// Basics.
    Rectbutton();
    ~Rectbutton();
    void free();
	void setIdentity( string identity );
	const string& getIdentity() const;
	
	void create( string line, string path, int size, int ply );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window, double elapsedTime );
	
	
	// Fades.
	void fadein( float v = 1, int max = 0xFF );
	void fadeinBorders( float v = 1, int max = 0xFF );
	void fadeinGlobal( float v = 1, int max = 0xFF );
	void fadeout( float v = 1, int min = 0 );
	void fadeoutBorders( float v = 1, int min = 0 );
	void fadeoutGlobal( float v = 1, int min = 0xFF );
	
	
	// Setters.
	void move( float x, float y );
	void setPosition( float x, float y );
	void center( float x, float y, int w, int h );
	void setColor( sf::Color color );
	void setColorText( sf::Color color );
	void setAlpha( float alpha = 0 );
	void setAlphaBorders( float alpha = 0 );
	
	
	// Getters.
	float getAlpha();
	float getAlphaBorders();
	sf::Uint8& getState();
	bool& getFocus();
	bool& getClicked();
	
	
	// Other accessors.
	const float& getX() const;
	const float& getY() const;
    const float getWidth() const;
    const float getHeight() const;
	
    const float& getLeft() const;
    const float getRight() const;
    const float& getTop() const;
    const float getBot() const;
	
	// Collision detection.
	bool checkCollision( float x, float y, float w = 0, float h = 0 );
};