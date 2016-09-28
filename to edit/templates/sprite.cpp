/**
    sprite.h
    Purpose: class MySprite to load and draw textures

    @author Adrian Michalek
    @version 2016.09.22
	@email adrmic98@gmail.com
*/


#include "sprite.h"
// #include <fstream>
#include <typeinfo>

#ifdef _WIN32
#include <windows.h>
#endif


MySprite::MySprite( int x, int y, sf::Uint8 alpha )
{
	name = "";
	
    sprite = NULL;
	texture = NULL;
	
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = alpha;
	
    width = 0;
	height = 0;
	left = x;
	top = y;
	
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
	
    width = 0;
	height = 0;
	left = 0;
	top = 0;
	
	nr = 0;
    offset = 0;
}





sf::Sprite& MySprite::get()
{
    if( nr == 0 || nr == 1 )
    {
        return *sprite;
    }
	
    return sprite[ offset ];
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
				width = texture->getSize().x;
				height = texture->getSize().y;
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
				width = texture->getSize().x / nr;
				height = texture->getSize().y;
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
			width = w;
			height = h;
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




/*
const string& MySprite::getTypeId()
{
	string str = typeid( nr ).name;
	
	return str;
}
*/




void MySprite::fadein( int v, int max )
{
	if( color.a < max )
	{
		int alpha = color.a + v;
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

void MySprite::fadeout( int v, int min )
{
	if( color.a > min )
	{
		int alpha = color.a - v;
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


int MySprite::getOffset()
{
	return offset;
}

void MySprite::setOffset( int n )
{
    offset = n;
}


void MySprite::setScale( float x, float y )
{
	width *= x;
	height *= y;
	
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




std::string MySprite::getName()
{
	return name;
}

void MySprite::setName( std::string name )
{
	this->name = name;
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
