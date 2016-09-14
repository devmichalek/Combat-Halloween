/**
    sprite.h
    Purpose: class MySprite to load and draw textures

    @author Adrian Michalek
    @version 2016.09.05
	@email adrmic98@gmail.com
*/


#include "sprite.h"

#ifdef _WIN32
#include <windows.h>
#endif

MySprite::MySprite( string ID )
{
	this->ID = ID;
	
    rect.width = 0;
	rect.height = 0;
	rect.left = 0;
	rect.right = 0;
	
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = 0xFF;

    nr = 0;
    offset = 0;
	
	pixels = NULL;
    sprite = NULL;
	texture = NULL;
}

MySprite::~MySprite()
{
    free();
}

void MySprite::free()
{
    rect.width = 0;
	rect.height = 0;
	rect.left = 0;
	rect.right = 0;
	
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = 0xFF;
	
	if( pixels != NULL )
    {
        delete [] pixels;
        pixels = NULL;
    }

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
	
	nr = 0;
    offset = 0;
}



#ifdef __linux__
void MySprite::load( string path, int nr )
{
    free();
	
	try
	{
		texture = new sf::Texture;
		if( texture == NULL )
		{
			throw "ID: " + ID + " \x1B[91mnot created\x1B[0m texture!";
		}
		else if( !texture->loadFromFile( path ) )
		{
			throw "ID: " + ID + " \x1B[91mnot loaded\x1B[0m " + path;
		}
		else
		{
			texture.setSmooth( true );
			
			this->nr = nr;
			if( nr < 1 )
			{
				throw "ID: " + ID + " \x1B[91mnumber is less than 1\x1B[0m";
			}
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
				throw "ID: " + ID + " \x1B[91mnot created\x1B[0m sprite!";
			}
			else
			{
				sprite->setTexture( texture );
				sprite->setColor( color );
				rect.width = texture.getSize().x;
				rect.height = texture.getSize().y;
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
				throw "ID: " + ID + " \x1B[91mnot created\x1B[0m array of sprite!";
			}
			else
			{
				rect.width = texture.getSize().x / nr;
				rect.height = texture.getSize().y;
			}
			
			sf::IntRect _rect;
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setTexture( texture);

				_rect.left = i * rect.width;
				_rect.top = 0;
				_rect.width = rect.width;
				_rect.height = rect.height;

				sprite[ i ].setTextureRect( _rect );
				sprite[ i ].setColor( color );
			}
		}
		catch( string msg )
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
			throw "ID: " + ID + " \x1B[91mwidth is less than 0\x1B[0m";
		if( h < 0 )
			throw "ID: " + ID + " \x1B[91mheight is less than 0\x1B[0m";
		
		if( !texture.create( w, h ) )
			throw "ID: " + ID + " \x1B[91mnot created blank texture\x1B[0m";
			
		sf::Uint8* pixels = new sf::Uint8[ w * h * 4 ];
		for( int i = 0; i < w*h*4; i += 4 )
		{
			pixels[ i ] = r;
			pixels[ i +1 ] = g;
			pixels[ i +2 ] = b;
			pixels[ i +3 ] = alpha;
		}
		
		nr = -2;
		texture.update( pixels );
		
		delete [] pixels;
		pixels = NULL;
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
	
	

	try
	{
		sprite = new sf::Sprite;
		if( sprite == NULL )
			throw "ID: " + ID + " \x1B[91mnot created\x1B[0m sprite!";
			
		sprite->setTexture( texture );
		this->w = texture.getSize().x;
		this->h = texture.getSize().y;
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}

#elif _WIN32
void MySprite::setColor( int i )
{
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( h, i );
}

void MySprite::load( string path, int nr )
{
    free();
	
	try
	{	
		if( !texture.loadFromFile( path ) )
		{
			throw "ID: " + ID + " ";
			setColor( 12 );
			throw "not loaded";
			setColor( 7 );
			throw " " + path;
		}
		texture.setSmooth( true );
		
		this->nr = nr;
		if( nr < 0 )
		{
			throw "ID: " + ID + " ";
			setColor( 12 );
			throw "number is less than 0";
			setColor( 7 );
		}
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
			{
				throw "ID: " + ID + " ";
				setColor( 12 );
				throw "not created";
				setColor( 7 );
				throw " sprite!";
			}
				
			sprite->setTexture( texture );
			sprite->setColor( sf::Color( r, g, b, alpha ) );
			
			w = texture.getSize().x;
			h = texture.getSize().y;
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
				throw "ID: " + ID + " ";
				setColor( 12 );
				throw "not created";
				setColor( 7 );
				throw " array of sprite!";
			}
				
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
		catch( string msg )
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
			throw "ID: " + ID + " width is less than 0";
		if( h < 0 )
			throw "ID: " + ID + " height is less than 0";
		
		if( !texture.create( w, h ) )
			throw "ID: " + ID + " not created blank texture";
			
		sf::Uint8* pixels = new sf::Uint8[ w * h * 4 ];
		for( int i = 0; i < w*h*4; i += 4 )
		{
			pixels[ i ] = r;
			pixels[ i +1 ] = g;
			pixels[ i +2 ] = b;
			pixels[ i +3 ] = alpha;
		}
		
		nr = -2;
		texture.update( pixels );
		
		delete [] pixels;
		pixels = NULL;
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
			throw "ID: " + ID + " ";
			setColor( 12 );
			throw "not created";
			setColor( 7 );
			throw " sprite!";
		}
			
		sprite->setTexture( texture );
		this->w = texture.getSize().x;
		this->h = texture.getSize().y;
	}
	catch( const char* msg )
	{
		cerr << msg << endl;
	}
}
#endif


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
		
		if( nr == -2 )
		{
			for( int i = 0; i < w*h*4; i += 4 )
			{
				//pixels[ i +3 ] = alpha;
			}
		}
		else if( nr == 0 || nr == 1 )
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
			
		if( nr == -2 )
		{
			for( int i = 0; i < w*h*4; i += 4 )
			{
				pixels[ i +3 ] = alpha;
			}
		}
		else if( nr == 0 || nr == 1 )
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

std::ostream& MySprite::operator <<( std::ostream& s )
{
	return s << "ID: " << ID << " x: " << x << " y: " << y << " w: " << w << " h: " << h << " alpha: " << alpha;
}

