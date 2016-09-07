/**
    sprite.h
    Purpose: class MySprite to load and draw textures

    @author Adrian Michalek
    @version 2016.09.05
	@email adrmic98@gmail.com
*/


#include "sprite.h"
#include <stdio.h>

MySprite::MySprite( int start_offset, int alpha )
{
    w = h = 0;
    x = y = 0;

    nr = -1;
    offset = start_offset;
	
    sprite = NULL;
	
	this->alpha = alpha;
	r = g = b = 0xFF;
}

MySprite::~MySprite()
{
    free();
}

void MySprite::free()
{
    w = h = 0;
    x = y = 0;

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
	
	nr = -1;

	alpha = 0;
	r = g = b = 0xFF;
}


void MySprite::load( string path, int nr )
{
    free();
	
	try
	{	
		if( !texture.loadFromFile( path ) )
			throw "\n\x1B[95mNot loaded\x1B[0m " + path + "\n";
		texture.setSmooth( true );
		
		this->nr = nr;
		if( nr < 0 )
			throw "\n\x1B[0mNumber is less than 0\x1B[0m\n";
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
    

	if( nr == 0 || nr == 1 )
	{
		try
		{
			sprite = new sf::Sprite;
			if( sprite == NULL )
				throw "\n\x1B[95mNot created\x1B[0m sprite!\n";
				
			sprite->setTexture( texture );
			sprite->setColor( sf::Color( r, g, b, alpha ) );
			
			w = texture.getSize().x;
			h = texture.getSize().y;
		}
		catch( const char* msg )
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
				throw "\n\x1B[95mNot created\x1B[0m array of sprite!\n";
				
			w = texture.getSize().x / nr;
			h = texture.getSize().y;
			
			sf::IntRect rect;
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setTexture( texture);

				rect.left = i * w;
				rect.top = 0;
				rect.width = w;
				rect.height = h;

				sprite[ i ].setTextureRect( rect );
				sprite[ i ].setColor( sf::Color( r, g, b, alpha ) );
			}
		}
		catch( const char* msg )
		{
			cerr << msg << endl;
		}
	}
}

void MySprite::create( int w, int h, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b )
{
	try
	{	
		
		if( w < 0 )
			throw "\n\x1B[0mWidth is less than 0\x1B[0m\n";
		if( h < 0 )
			throw "\n\x1B[0mWidth is less than 0\x1B[0m\n";
		
		if( !texture.create( w, h ) )
			throw "\n\x1B[0mNot created blank texture\x1B[0m\n";
			
		sf::Uint8* pixels = new sf::Uint8[ w * h * 4 ];
		for( int i = 0; i < w*h*4; i += 4 )
		{
			pixels[ i ] = r;
			pixels[ i +1 ] = g;
			pixels[ i +2 ] = b;
			pixels[ i +3 ] = alpha;
		}
		
		nr = 0;
		texture.update( pixels );
		
		delete [] pixels;
		pixels = NULL;
	}
	catch( const char* msg )
	{
		cerr << msg << endl;
	}
	
	

	try
	{
		sprite = new sf::Sprite;
		if( sprite == NULL )
			throw "\n\x1B[0mNot created\x1B[0m sprite!\n";
			
		sprite->setTexture( texture );
		this->w = texture.getSize().x;
		this->h = texture.getSize().y;
	}
	catch( const char* msg )
	{
		cerr << msg << endl;
	}
}


void MySprite::setOffset( int n )
{
    offset = n;
}

void MySprite::setPosition( float x, float y )
{
    this->x = x;
    this->y = y;

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


int MySprite::getAlpha()
{
	return alpha;
}

void MySprite::setAlpha( int alpha )
{
	if( this->alpha != alpha )
	{
		this->alpha = alpha;
		// printf( "new %salpha%s=%d\n", DGRAY, DEFAULT, this->alpha );
		
		if( nr == 0 || nr == 1 )
		{
			sprite->setColor( sf::Color( r, g, b, alpha ) );
		}
		else if( nr > 1 )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setColor( sf::Color( r, g, b, alpha ) );
			}
		}
	}
}


void MySprite::setColor( sf::Uint8 r, sf::Uint8 g, sf::Uint8 b )
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
		if( nr == 0 || nr == 1 )
		{
			sprite->setColor( sf::Color( r, g, b, alpha ) );
		}
		else if( nr > 1 )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setColor( sf::Color( r, g, b, alpha ) );
			}
		}
	}
}

void MySprite::setScale( float s, float z )
{
    if( nr == 0 || nr == 1 )
    {
        sprite->setScale( s, z );
    }
    else if( nr > 1 )
    {
        for( int i = 0; i < nr; i++ )
        {
            sprite[ i ].setScale( s, z );
        }
    }
}


sf::Sprite& MySprite::get()
{
    if( nr == 0 || nr == 1 )
    {
        return *sprite;
    }

    return sprite[ offset ];
}

bool MySprite::checkCollision( int x, int y, int w, int h )
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


void MySprite::fadein( int i, int max )
{
	if( alpha < max )
	{
		alpha += i;
		if( alpha > max )
			alpha = max;
			
		if( nr == 0 || nr == 1 )
		{
			sprite->setColor( sf::Color( r, g, b, alpha ) );
		}
		else if( nr > 1 )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setColor( sf::Color( r, g, b, alpha ) );
			}
		}
	}
}

void MySprite::fadeout( int i, int min )
{
	if( alpha > min )
	{
		alpha -= i;
		if( alpha < min )
			alpha = min;
			
		if( nr == 0 || nr == 1 )
		{
			sprite->setColor( sf::Color( r, g, b, alpha ) );
		}
		else if( nr > 1 )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setColor( sf::Color( r, g, b, alpha ) );
			}
		}
	}
}


int MySprite::getX()
{
    return x;
}

int MySprite::getY()
{
    return y;
}


int MySprite::getWidth()
{
    return w;
}
int MySprite::getHeight()
{
    return h;
}


int MySprite::getLeft()
{
    return x;
}

int MySprite::getRight()
{
    return x + w;
}


int MySprite::getTop()
{
    return y;
}

int MySprite::getBot()
{
    return y + h;
}

