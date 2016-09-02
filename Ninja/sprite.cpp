#include "sprite.h"
#include "stdio.h"

MySprite::MySprite( int offset, int alpha )
{
    w = 0;
    h = 0;
    x = 0;
    y = 0;
    scale = 1;

    nr = -1;
    this->offset = offset;
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
    w = 0;
    h = 0;
    x = 0;
    y = 0;
    scale = 1;

    if( nr == 0 || nr == 1 )
    {
        delete sprite;
        sprite = NULL;
    }

    if( nr > 1 )
    {
        delete [] sprite;
        sprite = NULL;
    }

    nr = -1;
	
	alpha = 0;
	r = g = b = 0xFF;
}

bool MySprite::load( string path, int nr )
{
    bool success = true;

    free();

    if( !texture.loadFromFile( path ) )
    {
		printf( "Can't load %s\n", path.c_str() );
        success = false;
    }
    else
    {
        texture.setSmooth( true );

        this->nr = nr;
        if( nr == 0 || nr == 1 )
        {
            sprite = new Sprite;
            if( sprite == NULL )
            {
                printf( "Not created sprite! - class MySprite\n" );
                success = false;
            }
            else
            {
                sprite->setTexture( texture );
				sprite->setColor( sf::Color( r, g, b, alpha ) );
                Vector2u sizes = texture.getSize();
                w = sizes.x;
                h = sizes.y;
            }
        }
        else if( nr > 1 )
        {
            sprite = new Sprite[ nr ];
            if( sprite == NULL )
            {
                printf( "Not created array of sprite! - class MySprite\n" );
                success = false;
            }
            else
            {
                Vector2u sizes = texture.getSize();
                w = sizes.x / nr;
                h = sizes.y;

                IntRect rect;

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
        }
        else
        {
            printf( "Wrong number! - class MySprite\n" );
            success = false;
        }
    }


    return success;
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

void MySprite::setColor( int r, int g, int b )
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



void MySprite::setScale( float s )
{
    scale = s;

    if( nr == 0 || nr == 1 )
    {
        sprite->setScale( s, s );
    }
    else if( nr > 1 )
    {
        for( int i = 0; i < nr; i++ )
        {
            sprite[ i ].setScale( s, s );
        }
    }
}

Sprite& MySprite::get()
{
    if( nr == 0 || nr == 1 )
    {
        return *sprite;
    }

    return sprite[ offset ];
}



int MySprite::getWidth()
{
    return w * scale;
}

int MySprite::getHeight()
{
    return h * scale;
}

int MySprite::getLeft()
{
    return x;
}

int MySprite::getRight()
{
    return x + w * scale;
}

int MySprite::getTop()
{
    return y;
}

int MySprite::getBot()
{
    return y + h * scale;
}

int MySprite::getX()
{
    return x;
}

int MySprite::getY()
{
    return y;
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

