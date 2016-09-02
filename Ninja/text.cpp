#include "text.h"
#include "stdio.h"

MyText::MyText( int alpha )
{
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
	
	font = new Font;
	if( !font->loadFromFile( path ) )
	{
		printf( "Can't load %s\n", path.c_str() );
		return false;
	}
	else
	{
		this->size = size;
		this->r = r;
		this->g = g;
		this->b = b;
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
	
	text = new Text;
	text->setString( line );
	text->setCharacterSize( size );
	text->setColor( sf::Color( r, g, b, alpha ) );
	text->setFont( *font );

	w = text->getCharacterSize() * line.length();
	h = text->getCharacterSize();
	
	return true;
}

	
void MyText::setPosition( float x, float y )
{
	this->x = x;
	this->y = y;
	text->setPosition( x, y );
	
	//printf( "%f  %f\n", x, y );
}


Text& MyText::get()
{
	return *text;
}

	
bool MyText::checkCollision( int x, int y, int w, int h )
{
	if( x + w > this->x && x < this->x + this->w )
	{
		if( y + h > this->y && y < this->y + this->h )
		{
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

void MyText::setColor( int r, int g, int b )
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
