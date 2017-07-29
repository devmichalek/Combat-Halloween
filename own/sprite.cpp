#include "sprite.h"
#include <math.h>

MySprite::MySprite()
{
	identity = "";
	image = NULL;
    sprite = NULL;
	texture = NULL;
	alpha = 0;
}

MySprite::~MySprite()
{
    free();
}

void MySprite::free()
{
	identity = "";
	
	if( image != NULL )
    {
        delete image;
        image = NULL;
    }
	
	if( sprite != NULL )
	{
		delete sprite;
		sprite = NULL;
	}
	
	if( texture != NULL )
	{
		delete texture;
		texture = NULL;
	}
	
	if( !rects.empty() )
	{
		for( unsigned i = 0; i < rects.size(); i++ )
		{
			delete rects[ i ];
			rects[ i ] = NULL;
		}
		
		rects.clear();
	}
	
	alpha = 0;
}

const sf::Sprite& MySprite::get() const
{
    return *sprite;
}



void MySprite::setIdentity( string identity )
{
	this->identity = identity;
}

const string& MySprite::getIdentity() const
{
	return identity;
}



void MySprite::setColor( sf::Color color )
{
	sf::Color newColor( sprite->getColor() );
	newColor.r = color.r;
	newColor.g = color.g;
	newColor.b = color.b;

	sprite->setColor( newColor );
}

void MySprite::setAlpha( float alpha )
{
	if( this->alpha != alpha )
	{
		this->alpha = alpha;
		sf::Color newColor( sprite->getColor() );
		newColor.a = alpha;
		sprite->setColor( newColor );
	}
}

float MySprite::getAlpha()
{
	return alpha;
}



void MySprite::fadein( float v, int max )
{
	if( alpha < max )
	{
		alpha += v;
		
		if( alpha > max )
		{
			alpha = max;
		}
		
		sf::Color newColor( sprite->getColor() );
		newColor.a = alpha;
		sprite->setColor( newColor );
	}
}

void MySprite::fadeout( float v, int min )
{
	if( alpha > min )
	{
		alpha -= v;
		
		if( alpha < min )
		{
			alpha = min;
		}
		
		sf::Color newColor( sprite->getColor() );
		newColor.a = alpha;
		sprite->setColor( newColor );
	}
}

void MySprite::flipHorizontally()
{
	sprite->setScale( sprite->getScale().x *-1, sprite->getScale().y );
}

void MySprite::flipVertically()
{
	sprite->setScale( sprite->getScale().x, sprite->getScale().y *-1 );
}



void MySprite::load( string path, int amount )
{
    free();
	
	// Load image.
	try
	{
		image = new sf::Image;
		if( image == NULL )
		{
			throw identity + " not created image";
		}
		else if( !image->loadFromFile( path ) )
		{
			throw identity + " not loaded " + path;
		}
		else if( amount < 1 )
		{
			throw identity + " amount of offsets is less than 1";
		}
		else
		{
			int width = image->getSize().x;
			int height = image->getSize().y;
			
			// Set rects and 0 offset
			for( int i = 0; i < amount; i++ )
			{
				rects.push_back( new sf::IntRect() );
				rects[ rects.size() -1 ]->width = width /amount;
				rects[ rects.size() -1 ]->height = height;
				rects[ rects.size() -1 ]->left = width *i /amount;
				rects[ rects.size() -1 ]->top = 0;
			}
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
	
	// Load texture and set sprite.
	try
	{
		texture = new sf::Texture;
		if( !texture->loadFromFile( path ) )
		{
			throw identity + " not loaded " + path;
		}
		else
		{
			texture->setSmooth( true );
			sprite = new sf::Sprite;
			if( sprite == NULL )
			{
				throw identity + " not created sprite";
			}
			else
			{
				sprite->setTexture( *texture );
				setOffset( 0 );
			}
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}

void MySprite::create( int w, int h )
{
	free();
	
	// Create texture.
	try
	{
		texture = new sf::Texture;
		if( !texture->create( w, h ) )
		{
			throw identity + " not loaded ";
		}
		else
		{
			texture->setSmooth( true );
			sprite = new sf::Sprite;
			if( sprite == NULL )
			{
				throw identity + " not created sprite";
			}
			else
			{
				sf::Uint8* pixels;
				pixels = new sf::Uint8 [ w * h * 4 ];
				
				for( int i = 0; i < w*h*4; i++ )
				{
					pixels[ i ] = 0xFF;
				}
				
				texture->update( pixels );
				
				delete [] pixels;
				pixels = NULL;
				
				sprite->setTexture( *texture );
				setOffset( 0 );
				alpha = 0xFF;
				setAlpha( 0 );
			}
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}




void MySprite::setPosition( float x, float y )
{
    sprite->setPosition( x, y );
}

void MySprite::move( float x, float y )
{
	sprite->move( x, y );
}

void MySprite::center( float x, float y, int w, int h )
{
	float left = w/2 - (image->getSize().x*sprite->getScale().x /rects.size())/2 + x;
    float top = h/2 - (image->getSize().y*sprite->getScale().y)/2 + y;

	sprite->setPosition( left, top );
}



void MySprite::setScale( float x, float y )
{
	sprite->setScale( x, y );
}

void MySprite::setOrigin( float x, float y )
{
	sprite->setOrigin( x, y );
}

void MySprite::setRotation( float angle )
{
	sprite->setRotation( angle );
}

float MySprite::getRotation()
{
	return sprite->getRotation();
}

void MySprite::setOffset( int n )
{
	if( n > -1 && n < static_cast <int> (rects.size()) )
	{
		sprite->setTextureRect( *rects[ n ] );
	}
}



const float& MySprite::getX() const
{
	return sprite->getPosition().x;
}

const float& MySprite::getY() const
{
	return sprite->getPosition().y;
}

const float MySprite::getWidth() const
{
	float scale = sprite->getScale().x;
	if( scale < 0 )	scale = -scale;
	return image->getSize().x *scale /rects.size();
}

const float MySprite::getHeight() const
{
	float scale = sprite->getScale().y;
	if( scale < 0 )	scale = -scale;
	return image->getSize().y *scale;
}

const float& MySprite::getLeft() const
{
	return sprite->getPosition().x;
}

const float MySprite::getRight() const
{
	return sprite->getPosition().x +getWidth();
}

const float& MySprite::getTop() const
{
	return sprite->getPosition().y;
}

const float MySprite::getBot() const
{
	return sprite->getPosition().y +getHeight();
}

bool MySprite::checkCollision( float x, float y, float w, float h )
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

bool MySprite::checkCollisionCircle( float x, float y )
{
	float r = getWidth() > getHeight() ? getWidth() : getHeight();
	r /= 2;
	float myX = getX() +getWidth() /2;
	float myY = getY() +getHeight() /2;
	
	float a = x -myX;
	float b = y -myY;
	
	if( sqrt((a*a) + (b*b)) <= r )
	{
		return true;
	}
	
	return false;
}

/*
bool MySprite::checkPixelCollision( int x, int y )
{
	if( x -left >= 0 && y -top >= 0 && x < left + width && y < top + height )
	{
		sf::Color c = image->getPixel( x -left, y -top );
		if( c.a > 0 )
		{
			return true;
		}
	}
	
	return false;
}
*/