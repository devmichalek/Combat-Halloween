#include "sprite.h"
#include "stdio.h"
#include "color.h"

MySprite::MySprite( int offset, int alpha )
{
    w = 0;
    h = 0;
    x = 0;
    y = 0;

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
		printf( "%sCan't load%s %s\n", LRED, DEFAULT, path.c_str() );
        success = false;
    }
    else
    {
        texture.setSmooth( true );

        this->nr = nr;
		
        if( nr == 0 || nr == 1 )
        {
            sprite = new sf::Sprite;
            if( sprite == NULL )
            {
                printf( "%sNot created%s sprite!\n", LRED, DEFAULT );
                success = false;
            }
            else
            {
                sprite->setTexture( texture );
				sprite->setColor( sf::Color( r, g, b, alpha ) );
                sf::Vector2u sizes = texture.getSize();
                w = sizes.x;
                h = sizes.y;
            }
        }
        else if( nr > 1 )
        {
            sprite = new sf::Sprite[ nr ];
            if( sprite == NULL )
            {
                printf( "%sNot created%s array of sprite!\n", LRED, DEFAULT );
                success = false;
            }
            else
            {
                sf::Vector2u sizes = texture.getSize();
                w = sizes.x / nr;
                h = sizes.y;

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
        }
        else
        {
            printf( "%sWrong%s number!\n", LRED, DEFAULT );
            success = false;
        }
		
		if( success )
			printf( "Sprite: %s, %snr%s=%d, w:%s%d%s h:%s%d%s\n", path.c_str(), BLUE, DEFAULT, nr, LCYAN, w, DEFAULT, LCYAN, h, DEFAULT );
    }


    return success;
}

bool MySprite::create( int w, int h, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b )
{
	if( !texture.create( w, h ) )
    {
		printf( "%sNot created%s blank texture\n", LRED, DEFAULT );
        return false;
    }
	else
	{
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
		
		sprite = new sf::Sprite;
		if( sprite == NULL )
		{
			printf( "%sNot created%s sprite!\n", LRED, DEFAULT );
			return false;
		}
		else
		{
			sprite->setTexture( texture );
			
			sf::Vector2u sizes = texture.getSize();
			this->w = sizes.x;
			this->h = sizes.y;
			
			printf( "Sprite: %sblank%s, %snr%s=%d, w:%s%d%s h:%s%d%s\n", BOLD, DEFAULT, BLUE, DEFAULT, nr, LCYAN, w, DEFAULT, LCYAN, h, DEFAULT );
			//printf( "set %sone%s w:%s%d%s h:%s%d%s\n", LYELLOW, DEFAULT, LCYAN, w, DEFAULT, LCYAN, h, DEFAULT );
			
			//printf( "%d  %d\n", w, h );
		}
	}
	
	return true;
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
		//printf( "new %sr%s=%d\n", LRED, DEFAULT, this->r );
		this->r = r;
		change = true;
	}
		
		
	if( this->g != g )
	{
		//printf( "new %sg%s=%d\n", LGREEN, DEFAULT, this->g );
		change = true;
		this->g = g;
	}
		
		
	if( this->b != b )
	{
		//printf( "new %sb%s=%d\n", LBLUE, DEFAULT, this->b );
		change = true;
		this->b = b;
	}
	
	if( change )
	{
		//printf( "%schange%s\n", GREEN, DEFAULT );
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
			// printf( "collision = %strue%s\n", GREEN, DEFAULT );
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

