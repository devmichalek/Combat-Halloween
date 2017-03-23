/**
    sprite.h
    Purpose: class MySprite to load and draw textures

    @author Adrian Michalek
    @version 2016.09.22
	@email adrmic98@gmail.com
*/


#include "sprite.h"

#ifdef _WIN32
#include <windows.h>
#endif




MySprite::MySprite()
{
	name = "";
	
    sprite = NULL;
	texture = NULL;
	image = NULL;
	
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = 0;
	
	nr = 0;
    offset = 0;
	
    safe_width = width = left = 0;
	safe_height = height = top = 0;
}

MySprite::~MySprite()
{
    free();
}

void MySprite::free()
{
	name = "";

    if( nr == 0 || nr == 1 )
    {
        delete sprite;
        sprite = NULL;
    }
    else if( nr > 1 )
    {
        delete [] sprite;
        sprite = NULL;
    }
	
	if( texture != NULL )
    {
        delete texture;
        texture = NULL;
    }
	
	if( image != NULL )
    {
        delete image;
        image = NULL;
    }
	
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = 0x00;
	
	nr = 0;
    offset = 0;
	
    safe_width = width = left = 0;
	safe_height = height = top = 0;
}



void MySprite::load( string path, int nr )
{
    free();
	
	try
	{
		image = new sf::Image;
		if( image == NULL )
		{
			throw name + " \x1B[91mnot created\x1B[0m image";
		}
		else if( !image->loadFromFile( path ) )
		{
			throw name + " \x1B[91mnot loaded\x1B[0m " + path;
		}
		
		texture = new sf::Texture;
		if( texture == NULL )
		{
			throw name + " \x1B[91mnot created\x1B[0m texture";
		}
		else if( !texture->loadFromFile( path ) )
		{
			throw name + " \x1B[91mnot loaded\x1B[0m " + path;
		}
		else
		{
			texture->setSmooth( true );
			
			if( nr < 1 )	throw name + " \x1B[91mnumber is less than 1\x1B[0m";
			else			this->nr = nr;
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
    

	if( nr == 1 )
	{
		try
		{
			sprite = new sf::Sprite;
			if( sprite == NULL )
			{
				throw name + " \x1B[91mnot created\x1B[0m sprite";
			}
			else
			{
				sprite->setTexture( *texture );
				sprite->setColor( color );
				safe_width = width = texture->getSize().x;
				safe_height = height = texture->getSize().y;
			}
		}
		catch( string msg )
		{
			cerr << msg << endl;
		}
	}
	else if( nr > 1 )
	{
		try
		{
			sprite = new sf::Sprite[ nr ];
			if( sprite == NULL )
			{
				throw name + " \x1B[91mnot created\x1B[0m array of sprite";
			}
			else
			{
				safe_width = width = texture->getSize().x / nr;
				safe_height = height = texture->getSize().y;
			}
			
			sf::IntRect r;	// temporary rectangle
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setTexture( *texture );
				sprite[ i ].setTextureRect( sf::IntRect( i * width, 0, width, height ) );
				sprite[ i ].setColor( color );
			}
		}
		catch( string msg )
		{
			cerr << msg << endl;
		}
	}
}

void MySprite::create( int w, int h )
{
	free();
	
	try
	{	
		if( w < 0 )
		{
			throw name + " \x1B[91mwidth is less than 0\x1B[0m";
		}
		if( h < 0 )
		{
			throw name + " \x1B[91mheight is less than 0\x1B[0m";
		}
		
		texture = new sf::Texture;
		if( texture == NULL )
		{
			throw name + " \x1B[91mnot created\x1B[0m texture";
		}
		else if( !texture->create( w, h ) )
		{
			throw name + " \x1B[91mnot created blank texture\x1B[0m";
		}
		else
		{
			sf::Uint8* pixels;
			pixels = new sf::Uint8 [ w * h * 4 ];
			
			for( int i = 0; i < w*h*4; i++ )
			{
				pixels[ i ] = 0xFF;
			}
			
			nr = 0;
			
			texture->update( pixels );
			
			delete [] pixels;
			pixels = NULL;
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
	
	try
	{
		sprite = new sf::Sprite;
		if( sprite == NULL )
		{
			throw name + " \x1B[91mnot created\x1B[0m sprite";
		}
		else
		{
			sprite->setTexture( *texture );
			safe_width = width = w;
			safe_height = height = h;
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}



void MySprite::fadein( int v, int max )
{
	if( color.a < max )
	{
		int alpha = color.a + v;
		
		if( alpha > max )
		{
			alpha = max;
		}
		
		color.a = alpha;
		
		if( nr == 0 || nr == 1 )
		{
			sprite->setColor( color );
		}
		else if( nr > 1 )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setColor( color );
			}
		}
	}
}

void MySprite::fadeout( int v, int min )
{
	if( color.a > min )
	{
		int alpha = color.a - v;
		
		if( alpha < min )
		{
			alpha = min;
		}
		
		color.a = alpha;

		if( nr == 0 || nr == 1 )
		{
			sprite->setColor( color );
		}
		else if( nr > 1 )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setColor( color );
			}
		}
	}
}



void MySprite::setScale( float x, float y )
{
    if( nr == 0 || nr == 1 )
    {
        sprite->setScale( x, y );
    }
    else if( nr > 1 )
    {
        for( int i = 0; i < nr; i++ )
        {
            sprite[ i ].setScale( x, y );
        }
    }
	
	if( x < 0 ) x = -x;
	if( y < 0 ) y = -y;
	
	width = safe_width * x;
	height = safe_height * y;
}

const sf::Sprite& MySprite::get() const
{
    if( nr == 0 || nr == 1 )
    {
        return *sprite;
    }
	
    return sprite[ offset ];
}



void MySprite::setPosition( float x, float y )
{
    left = x;
    top = y;

    if( nr == 0 || nr == 1 )
    {
        sprite->setPosition( x, y );
    }
    else if( nr > 1 )
    {
        for( int i = 0; i < nr; i++ )
        {
            sprite[ i ].setPosition( x, y );
        }
    }
}

void MySprite::center( int x, int y, int w, int h )
{
	left = w/2 - width/2 + x;
    top = h/2 - height/2 + y;

    if( nr == 0 || nr == 1 )
    {
        sprite->setPosition( left, top );
    }
    else if( nr > 1 )
    {
        for( int i = 0; i < nr; i++ )
        {
            sprite[ i ].setPosition( left, top );
        }
    }
}



void MySprite::setColor( sf::Color color )
{
	bool change = false;
	if( this->color.r != color.r )
	{
		this->color.r = color.r;
		change = true;
	}
	
	if( this->color.g != color.g )
	{
		this->color.g = color.g;
		change = true;
	}
	
	if( this->color.b != color.b )
	{
		this->color.b = color.b;
		change = true;
	}
	
	if( change )
	{
		if( nr == 0 || nr == 1 )
		{
			sprite->setColor( this->color );
		}
		else if( nr > 1 )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setColor( this->color );
			}
		}
	}
}

void MySprite::setAlpha( sf::Uint8 a )
{
	if( color.a != a )
	{
		color.a = a;
		
		if( nr == 0 || nr == 1 )
		{
			sprite->setColor( color );
		}
		else if( nr > 1 )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setColor( color );
			}
		}
	}
}

void MySprite::setOffset( int n )
{
    offset = n;
}

const int& MySprite::getOffset() const
{
	return offset;
}

void MySprite::setName( std::string name )
{
	this->name = name;
}

const std::string& MySprite::getName() const
{
	return name;
}



bool MySprite::checkPixelCollision( int x, int y )
{
	if( x -left >= 0 && y -top >= 0 && x < left + width && y < top + height )
	{
		sf::Color c = image->getPixel( x -left, y -top );
		if( c.a > 0 )
		{
			// printf( "%d %d    x%d y%d xw%d yh%d\n", x, y, left, top, left + width, top + height );
			return true;
		}
	}
	
	return false;
}



bool MySprite::operator ==( MySprite& mySprite )
{
	if( width == mySprite.getWidth() && height == mySprite.getHeight() )
	{
		if( color == mySprite.getColor() )
		{
			if( name == mySprite.getName() )
			{
				return true;
			}
		}
	}
	
	return false;
}

bool MySprite::operator >( MySprite& mySprite )
{
	if( width > mySprite.getWidth() && height > mySprite.getHeight() )
	{
		return true;
	}
	
	return false;
}

bool MySprite::operator >=( MySprite& mySprite )
{
	if( width >= mySprite.getWidth() && height >= mySprite.getHeight() )
	{
		return true;
	}
	
	return false;
}

bool MySprite::operator <( MySprite& mySprite )
{
	if( width < mySprite.getWidth() && height < mySprite.getHeight() )
	{
		return true;
	}
	
	return false;
}

bool MySprite::operator <=( MySprite& mySprite )
{
	if( width <= mySprite.getWidth() && height <= mySprite.getHeight() )
	{
		return true;
	}
	
	return false;
}

std::ostream& MySprite::operator <<( std::ostream& str )
{
	std::string result = "";
	result += name;
	result += " x: " + left;
	result += " y: " + top;
	result += " w: " + width;
	result += " h: " + height;
	result += " alpha: " + color.a;
	
	return str << result;
}