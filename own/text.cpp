#include "text.h"

MyText::MyText()
{
	identity = "";
    font = NULL;
	text = NULL;
	alpha = 0;
}

MyText::~MyText()
{
	free();
}

void MyText::free()
{
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
	
	alpha = 0;
}

const sf::Text& MyText::get() const
{
	return *text;
}

sf::Font* MyText::getFont() const
{
	return font;
}



void MyText::setIdentity( string identity )
{
	this->identity = identity;
}

const string& MyText::getIdentity() const
{
	return identity;
}



void MyText::setFont( string path )
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
			throw identity + " not loaded " + path;
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}

void MyText::setFontByFont( sf::Font* newFont )
{
	this->font = newFont;
}

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
		{
			throw identity + " not created text object";
		}
			
		text->setString( line );
		text->setFont( *font );
		sf::Color newColor( text->getColor() );
		newColor.a = alpha;
		text->setColor( newColor );
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}

void MyText::setTextW( wstring line )
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
		{
			throw identity + " not created text object";
		}
			
		text->setString( line );
		text->setFont( *font );
		sf::Color newColor( text->getColor() );
		newColor.a = alpha;
		text->setColor( newColor );
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}



void MyText::fadein( float v, int max )
{
	if( alpha < max )
	{
		alpha += v;
		
		if( alpha > max )
		{
			alpha = max;
		}
		
		sf::Color newColor( text->getColor() );
		newColor.a = alpha;
		text->setColor( newColor );
	}
}

void MyText::fadeout( float v, int min )
{
	if( alpha > min )
	{
		alpha -= v;
		
		if( alpha < min )
		{
			alpha = min;
		}

		sf::Color newColor( text->getColor() );
		newColor.a = alpha;
		text->setColor( newColor );
	}
}

void MyText::flipHorizontally()
{
	text->setScale( text->getScale().x *-1, text->getScale().y );
}

void MyText::flipVertically()
{
	text->setScale( text->getScale().x, text->getScale().y *-1 );
}



void MyText::setPosition( float x, float y )
{
	text->setPosition( x, y );
}

void MyText::move( float x, float y )
{
	text->move( x, y );
}

void MyText::center( float x, float y, int w, int h )
{
	float left = x +(w/2 - text->getLocalBounds().width/2);
    float top = y +(h/2 - text->getLocalBounds().height/2);

	text->setPosition( left, top );
}




void MyText::setScale( float x, float y )
{
	text->setScale( x, y );
}

void MyText::setSize( int size )
{
	text->setCharacterSize( size );
}

int MyText::getSize()
{
	return text->getCharacterSize();
}

void MyText::setRotation( float angle )
{
	text->setRotation( angle );
}



void MyText::setAlpha( float alpha )
{
	if( this->alpha != alpha )
	{
		this->alpha = alpha;
		sf::Color newColor( text->getColor() );
		newColor.a = alpha;
		text->setColor( newColor );
	}
}

float MyText::getAlpha()
{
	return alpha;
}

void MyText::setColor( sf::Color color )
{
	sf::Color newColor( text->getColor() );
	newColor.r = color.r;
	newColor.g = color.g;
	newColor.b = color.b;

	text->setColor( newColor );
}



const float& MyText::getX() const
{
	return text->getPosition().x;
}

const float& MyText::getY() const
{
	return text->getPosition().y;
}

const float MyText::getWidth() const
{
	float scale = text->getScale().x;
	if( scale < 0 )	scale = -scale;
	return text->getLocalBounds().width *scale;
}

const float MyText::getHeight() const
{
	float scale = text->getScale().y;
	if( scale < 0 )	scale = -scale;
	
	return text->getLocalBounds().height *scale;
}

const float& MyText::getLeft() const
{
	return text->getPosition().x;
}

const float MyText::getRight() const
{
	return text->getPosition().x +getWidth();
}

const float& MyText::getTop() const
{
	return text->getPosition().y;
}

const float MyText::getBot() const
{
	return text->getPosition().y +getHeight();
}

bool MyText::checkCollision( float x, float y, float w, float h )
{
	if( y + h <= getTop() )
        return false;

    if( y >= getBot() )
        return false;

    if( x + w <= getLeft() )
        return false;

    if( x >= getRight() )
        return false;

    return true;
}