/**
    text.cpp
    Purpose: class MyText to load and draw text

    @author Adrian Michalek
    @version 2016.09.07
	@email adrmic98@gmail.com
*/


#include "text.h"

#ifdef _WIN32
#include <windows.h>
#endif

MyText::MyText( int alpha )
{
	ID = "";
	
	w = h = 0;
    x = y = 0;

    font = NULL;
	text = NULL;
	
	size = 0;
	
	this->alpha = alpha;
	r = g = b = 0xFF;
}

MyText::~MyText()
{
	free();
}

void MyText::free()
{
	w = h = 0;
    x = y = 0;

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
	alpha = 0;
	r = g = b = 0xFF;
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
	
	this->r = r;
	this->g = g;
	this->b = b;
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
	
	this->r = r;
	this->g = g;
	this->b = b;
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
		text->setColor( sf::Color( r, g, b, alpha ) );
		text->setFont( *font );
		
		w = text->getLocalBounds().width;
		h = text->getLocalBounds().height;
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}
	
void MyText::setPosition( float x, float y )
{
	this->x = x;
	this->y = y;
	text->setPosition( x, y );
}

void MyText::setScale( float w, float h )
{
	this->w = w;
	this->h = h;
	text->setScale( w, h );
}


sf::Text& MyText::get()
{
	return *text;
}

bool MyText::checkCollision( int x, int y, int w, int h )
{
	if( x + w > this->x && x < this->x + this->w )
	{
		if( y + h > this->y && y < this->y + this->h )
		{
			// printf( "collision = %strue%s\n", LGREEN, DEFAULT );
			return true;
		}
	}
	
	return false;
}


void MyText::fadein( int i, int max )
{
	if( alpha < max )
	{
		alpha += i;
		if( alpha > max )
			alpha = max;

		text->setColor( sf::Color( r, g, b, alpha ) );
	}
}

void MyText::fadeout( int i, int min )
{
	if( alpha > min )
	{
		alpha -= i;
		if( alpha < min )
			alpha = min;

		text->setColor( sf::Color( r, g, b, alpha ) );
	}
}


void MyText::setColor( sf::Uint8 r, sf::Uint8 g, sf::Uint8 b )
{
	bool change = false;
	
	if( this->r != r )
	{
		this->r = r;
		change = true;
	}
		
	if( this->g != g )
	{
		change = true;
		this->g = g;
	}
		
	if( this->b != b )
	{
		change = true;
		this->b = b;
	}
	
	if( change )	text->setColor( sf::Color( r, g, b, alpha ) );
}

void MyText::setSize( int size )
{
	if( this->size != size )
	{
		this->size = size;
		text->setCharacterSize( size );
	}
}


int MyText::getAlpha()
{
	return alpha;
}

void MyText::setAlpha( int alpha )
{
	if( this->alpha != alpha )
	{
		this->alpha = alpha;
		text->setColor( sf::Color( r, g, b, alpha ) );
	}
}


int MyText::getX()
{
    return x;
}

int MyText::getY()
{
    return y;
}


int MyText::getWidth()
{
    return w;
}

int MyText::getHeight()
{
    return h;
}


int MyText::getLeft()
{
    return x;
}

int MyText::getRight()
{
    return x + w;
}


int MyText::getTop()
{
    return y;
}

int MyText::getBot()
{
    return y + h;
}

std::ostream& MyText::operator <<( std::ostream& s )
{
	return s << "ID: " << ID << " x: " << x << " y: " << y << " w: " << w << " h: " << h << " alpha: " << alpha;
}