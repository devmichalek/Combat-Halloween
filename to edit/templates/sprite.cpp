/**
    sprite.h
    Purpose: class MySprite to load and draw textures

    @author Adrian Michalek
    @version 2016.09.05
	@email adrmic98@gmail.com
*/


#include "sprite.h"
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif


MySprite::MySprite()
{
	name = "";
	
    sprite = NULL;
	texture = NULL;
	
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = 0x00;
	
    rect.width = 0;
	rect.height = 0;
	rect.left = 0;
	rect.top = 0;
	
    nr = 0;
    offset = 0;
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
	
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = 0x00;
	
    rect.width = 0;
	rect.height = 0;
	rect.left = 0;
	rect.top = 0;
	
	nr = 0;
    offset = 0;
}

void MySprite::setName( string name )
{
	this->name = name;
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
				rect.width = texture->getSize().x;
				rect.height = texture->getSize().y;
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
				rect.width = texture->getSize().x / nr;
				rect.height = texture->getSize().y;
			}
			
			sf::IntRect r;	// temporary rectangle
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setTexture( *texture );
				sprite[ i ].setTextureRect( sf::IntRect( i * rect.width, 0, rect.width, rect.height ) );
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
			
			sf::Uint8 pixels[ w * h * 4 ];
			for( int i = 0; i < w*h*4; i++ )
			{
				pixels[ i ] = 0xFF;
			}
			nr = 0;
			texture->update( pixels );
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
			rect.width = w;
			rect.height = h;
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
}
#endif








void MySprite::setPosition( float x, float y )
{
    this->rect.left = x;
    this->rect.top = y;

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

void MySprite::center( int w, int h, int wm, int hm )
{
	rect.left = w/2 - rect.width/2 + wm;
    rect.top = h/2 - rect.height/2 + hm;

    if( nr == 0 || nr == 1 )
    {
        sprite->setPosition( rect.left, rect.top );
    }
    else if( nr > 1 )
    {
        for( int i = 0; i < nr; i++ )
        {
            sprite[ i ].setPosition( rect.left, rect.top );
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

void MySprite::setScale( float x, float y )
{
	rect.width *= x;
	rect.height *= y;
	
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
}





bool MySprite::checkCollision( int x, int y, int w, int h )
{
	if( x + w > rect.left && x < rect.left + rect.width )
	{
		if( y + h > rect.top && y < rect.top + rect.height )
		{
			return true;
		}
	}
	
	return false;
}


void MySprite::fadein( int i, int max )
{
	if( color.a < max )
	{
		int alpha = color.a + i;
		if( alpha > max )
			alpha = max;
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

void MySprite::fadeout( int i, int min )
{
	if( color.a > min )
	{
		int alpha = color.a - i;
		if( alpha < min )
			alpha = min;
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


sf::Uint8 MySprite::getAlpha()
{
	return color.a;
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


int MySprite::getX()
{
    return rect.left;
}
int MySprite::getY()
{
    return rect.top;
}

int MySprite::getWidth()
{
    return rect.width;
}
int MySprite::getHeight()
{
    return rect.height;
}


int MySprite::getLeft()
{
    return rect.left;
}
int MySprite::getRight()
{
    return rect.left + rect.width;
}

int MySprite::getTop()
{
    return rect.top;
}
int MySprite::getBot()
{
    return rect.top + rect.height;
}


void MySprite::setOffset( int n )
{
    offset = n;
}
int MySprite::getOffset()
{
	return offset;
}


sf::Sprite& MySprite::get()
{
    if( nr == 0 || nr == 1 )
    {
        return *sprite;
    }
	
    return sprite[ offset ];
}

std::ostream& MySprite::operator <<( std::ostream& s )
{
	return s << name << " x: " << rect.left << " y: " << rect.top << " w: " << rect.width << " h: " << rect.height << " alpha: " << color.a;
}

/*
void MySprite::createTxt( string name, string path )
{
	fstream file;
	
	file.open( name.c_str(), std::ios::out | std::ios::app );
	if( file.bad() )
	{
		printf( "Can not create file %s\n", name.c_str() );
	}
	else
	{
		try
		{
			sf::Texture tex;
			if( !tex.loadFromFile( path ) )
			{
				throw name + " \x1B[91mnot loaded\x1B[0m " + path;
			}
			else
			{
				tex.setSmooth( true );
				
				sf::Image image = tex.copyToImage();
				int w = tex.getSize().x;
				int h = tex.getSize().y;
				
				file << std::to_string( w ) << " " << std::to_string( h ) << "\n";
				// printf( "%d %d\n", w, h );
				
				// int counter = 0;
				// Following red, green, blue, alpha of texture
				for( int i = 0; i < h; i++ )
				{
					for( int j = 0; j < w; j++ )
					{
						file << std::to_string( static_cast <int> ( image.getPixel( i, j ).r ) ) << " ";
						file << std::to_string( static_cast <int> ( image.getPixel( i, j ).g ) ) << " ";
						file << std::to_string( static_cast <int> ( image.getPixel( i, j ).b ) ) << " ";
						file << std::to_string( static_cast <int> ( image.getPixel( i, j ).a ) ) << " ";
						// counter += 4;
					}
				}
				
				// printf( "Counter %d\n", counter );
			}
		}
		catch( string msg )
		{
			cerr << msg << endl;
		}
		
	}
}

void MySprite::loadTxt( string path )
{
	free();
	
	fstream file;
	
	file.open( path.c_str(), std::ios::in );
	if( file.bad() )
	{
		printf( "Can not load file %s\n", path.c_str() );
	}
	else
	{
		file >> rect.width;
		file >> rect.height;
		
		// printf( "%d %d", rect.width, rect.height );
		
		try
		{
			texture = new sf::Texture;
			if( texture == NULL )
			{
				throw name + " \x1B[91mnot created\x1B[0m texture";
			}
			else if( !texture->create( rect.width, rect.height ) )
			{
				throw name + " \x1B[91mnot created blank texture\x1B[0m";
			}
			else
			{
				pixels = new sf::Uint8[ rect.width * rect.height * 4 ];
				if( pixels == NULL )
				{
					throw name + " \x1B[91mnot created\x1B[0m array of pixels";
				}
				else
				{
					this->color = color;
					this->color.a = 0x00;
					
					int led;
					// int counter = 0;
					for( int i = 0; i < rect.width*rect.height*4; i ++ )
					{
						file >> led;
						pixels[ i ] = static_cast <sf::Uint8> ( led );
						// counter ++;
					}
					
					// printf( "Counter %d\n", counter );
				}
				
				nr = 0;
				texture->update( pixels );
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
			}
		}
		catch( string msg )
		{
			cerr << msg << endl;
		}
	}
}
*/
