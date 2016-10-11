/**
    text.cpp
    Purpose: class MyText to load and draw text

    @author Adrian Michalek
    @version 2016.09.07
	@email adrmic98@gmail.com
*/


#include "text.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

MyText::MyText( int x, int y, sf::Uint8 alpha )
{
	ID = "";
	
	width = height = 0;
    left = x;
	top = y;

    font = NULL;
	text = NULL;
	
	size = 0;
	
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = alpha;
}

MyText::~MyText()
{
	free();
}

void MyText::free()
{
	width = height = 0;
    left = top = 0;

    if( font != NULL )
    {
        delete font;
        font = NULL;
    }
	
	if( text != NULL )
    {
        delete text;
        text = NULL;
    }
	
	size = 0;
	
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = 0x00;
}

void MyText::setID( string name )
{
	ID = name;
}


#ifdef __linux__
void MyText::setFont( string path, int size, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b )
{
	if( font != NULL )
    {
        delete font;
        font = NULL;
    }
	
	try
	{
		font = new sf::Font;

		if( !font->loadFromFile( path ) )
			throw "ID: " + ID + " \x1B[91mnot loaded\x1B[0m " + path;
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
	
	try
	{
		this->size = size;
		if( size < 1 )
			throw "ID: " + ID + " \x1B[91msize is less than 1!\x1B[0m";
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
	
	this->color = sf::Color( r, g, b, 0x00 );
}
#elif _WIN32
void MyText::setColor( int i )
{
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( h, i );
}

void MyText::setFont( string path, int size, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b )
{
	if( font != NULL )
    {
        delete font;
        font = NULL;
    }
	
	try
	{
		font = new sf::Font;

		if( !font->loadFromFile( path ) )
		{
			throw "ID: " + ID + " ";
			setColor( 12 );
			throw "not loaded";
			setColor( 7 );
			throw " " + path;
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
	
	try
	{
		this->size = size;
		if( size < 1 )
		{
			throw "ID: " + ID + " ";
			setColor( 12 );
			throw "size is less than 1!";
			setColor( 7 );
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
	
	this->color = sf::Color( r, g, b, 0x00 );
}
#endif


void MyText::setText( string line )
{
	if( text != NULL )
    {
        delete text;
        text = NULL;
    }
	
	try
	{
		text = new sf::Text;
		
		if( text == NULL )
			throw "ID: " + ID + " not created text object";
		
		text->setString( line );
		text->setCharacterSize( size );
		text->setColor( color );
		text->setFont( *font );
		
		width = text->getLocalBounds().width;
		height = text->getLocalBounds().height;
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}
	
void MyText::setPosition( float x, float y )
{
	this->left = x;
	this->top = y;
	
	text->setPosition( left, top );
}

void MyText::center( int w, int h, int wm, int hm )
{
	this->left = w/2 - this->width/2 + wm;
    this->top = h/2 - this->height/2 + hm;

	text->setPosition( left, top );
}

void MyText::setScale( float w, float h )
{
	this->width = w;
	this->height = h;
	
	text->setScale( w, h );
}


sf::Text& MyText::get()
{
	return *text;
}


void MyText::fadein( int v, int max )
{
	if( color.a < max )
	{
		int alpha = color.a +v;
		if( alpha > max )
			alpha = max;
		color.a = alpha;

		text->setColor( color );
	}
}

void MyText::fadeout( int v, int min )
{
	if( color.a > min )
	{
		int alpha = color.a -v;
		if( alpha < min )
			alpha = min;
		color.a = alpha;

		text->setColor( color );
	}
}


void MyText::setColor( sf::Uint8 r, sf::Uint8 g, sf::Uint8 b )
{
	bool change = false;
	if( this->color.r != r )
	{
		this->color.r = r;
		change = true;
	}
	
	if( this->color.g != g )
	{
		this->color.g = g;
		change = true;
	}
	
	if( this->color.b != b )
	{
		this->color.b = b;
		change = true;
	}
	
	if( change )
		text->setColor( this->color );
}

void MyText::setSize( int size )
{
	if( this->size != size )
	{
		this->size = size;
		text->setCharacterSize( size );
	}
}



void MyText::setAlpha( sf::Uint8 alpha )
{
	if( this->color.a != alpha )
	{
		this->color.a = alpha;
		text->setColor( color );
	}
}


std::ostream& MyText::operator <<( std::ostream& s )
{
	return s << "ID: " << ID << " x: " << left << " y: " << top << " w: " << width << " h: " << height << " alpha: " << color.a;
}

void MyText::reloadPosition()
{
	text->setPosition( left, top );
}