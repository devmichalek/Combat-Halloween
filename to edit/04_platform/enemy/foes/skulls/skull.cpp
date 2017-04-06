#include "skull.h"
#include "file/file.h"

Skull::Skull()
{
	free();
}

Skull::~Skull()
{
	free();
}

void Skull::free()
{
	sprite.free();
	
	x = y = 0;
	g_x = g_y = 0;
	screen_w = 0;
	screen_h = 0;
	angle = 0;
	
	offset = 0;
	delay = 0;
	line = 0;
	
	alpha = 0;
	alpha_state = false;
	state = 0;
	
	vel = 0;
	scale = 0;
	
	counter = 0;
	counter_line = 0;
}

void Skull::reset()
{
	angle = 0;
	offset = 0;
	alpha = 0;
	alpha_state = false;
	state = 0;
	counter = 0;
}



void Skull::load( int screen_w, int screen_h, string path )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Set stuff.
	MyFile file;
	file.load( "data/txt/enemy/skull/" +path +".txt" );
	if( file.is_good() )
	{
		string l;
		
		// Set line.
		file.get() >> l;
		line = con::stoi( l );
		
		// Set delay.
		file.get() >> l;
		delay = con::stoi( l );
		
		// Set velocity.
		file.get() >> l;
		vel = con::stof( l.c_str() );
		
		// Set scale.
		file.get() >> l;
		scale = con::stof( l.c_str() );
	}
	file.free();
	
	sprite.setName( "skull-sprite" );
	sprite.load( "data/04_platform/enemy/skull/"+path +".png", line );
	sprite.setOrigin( sprite.getWidth() /2, sprite.getHeight() /2 );
	sprite.setScale( scale, scale );
	
	counter_line = 300;
}

void Skull::draw( sf::RenderWindow* &window )
{
	if( state > 0 && sprite.getRight() > 0 && sprite.getX() < screen_w +sprite.getWidth() )
	{
		sprite.setOffset( offset /delay );
		window->draw( sprite.get() );
	}
}



void Skull::fadein( int j, int max )
{
	if( !alpha_state )
	{
		sprite.fadein( j, max );
		alpha = sprite.getAlpha();
		if( alpha == max )
		{
			alpha_state = true;
		}
	}
}

void Skull::fadeout( int j, int min )
{
	sprite.fadeout( j, min );
	alpha = sprite.getAlpha();
}




void Skull::moveX( sf::Uint8 d, float v )
{
	if( d == 1 )
	{
		x += v;
	}
	else if( d == 2 )
	{
		x -= v;
	}
	
	sprite.setPosition( x, sprite.getY() );
}

void Skull::undoFall( sf::Uint8 add )
{
	x += add;
	sprite.setPosition( x, sprite.getY() );
}

void Skull::mechanics( int x, int y )
{
	
}

void Skull::setColor( sf::Color color )
{
	sprite.setColor( color );
}