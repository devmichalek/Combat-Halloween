#include "text.h"
#include <stdio.h>
#include "color.h"

/*
template <int num>
bool bar()
{
    static bool flag = true;
	bool buf = flag;
	flag = false;
	return buf;
}
*/

MyText::MyText( int alpha )
{
	//static int c = 0;
	state = 0;
	//c++;
	
	w = 0;
    h = 0;
    x = 0;
    y = 0;

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
	w = 0;
    h = 0;
    x = 0;
    y = 0;

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

	
bool MyText::setFont( string path, int size, int r, int g, int b )
{
	if( font != NULL )
    {
        delete font;
        font = NULL;
    }
	
	font = new sf::Font;
	if( !font->loadFromFile( path ) )
	{
		printf( "%sCan't load%s %s\n", LRED, DEFAULT, path.c_str() );
		return false;
	}
	else
	{
		this->size = size;
		this->r = r;
		this->g = g;
		this->b = b;
		
		printf( "Font: %s, %ssize%s:%d R:%s0x%02x%s G:%s0x%02x%s B:%s0x%02x%s\n",path.c_str(), DGRAY, DEFAULT, size,
		LMAGENTA, r, DEFAULT, LMAGENTA, g, DEFAULT, LMAGENTA, b, DEFAULT );
	}
	
	return true;
}

bool MyText::setText( string line )
{
	if( text != NULL )
    {
        delete text;
        text = NULL;
    }
	
	text = new sf::Text;
	text->setString( line );
	text->setCharacterSize( size );
	text->setColor( sf::Color( r, g, b, alpha ) );
	text->setFont( *font );
	
	// printf( "%s\n", line.c_str() );
	
	w = text->getLocalBounds().width;
	h = text->getLocalBounds().height;
	
	// if( bar<state>() )	
	if( state == 0 )// if it's first loading
		printf( "Text: %s%s%s w:%s%d%s h:%s%d%s\n", DGRAY, line.c_str(), DEFAULT, LCYAN, w, DEFAULT, LCYAN, h, DEFAULT );
	state ++;
	
	return true;
}

	
void MyText::setPosition( float x, float y )
{
	this->x = x;
	this->y = y;
	text->setPosition( x, y );
	
	//printf( "%f  %f\n", x, y );
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
	
	if( change )
	{
		text->setColor( sf::Color( r, g, b, alpha ) );
	}
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

int MyText::getX()
{
    return x;
}

int MyText::getY()
{
    return y;
}
