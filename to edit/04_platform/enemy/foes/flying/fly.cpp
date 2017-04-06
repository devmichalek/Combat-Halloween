#include "fly.h"
#include "file/file.h"

Fly::Fly()
{
	free();
}

Fly::~Fly()
{
	free();
}

void Fly::free()
{
	x = 0;
	y = 0;
	screen_w = 0;
	screen_h = 0;
	
	sprite.free();
	
	offset = 0;
	delay = 0;
	line = 0;
	
	alpha = 0;
	alpha_state = false;
	state = 0;
	
	direction = 0;
	
	vel = 0;
	scale = 0;
	
	counter = 0;
	counter_line = 0;
	
	floor = 0;
	floor_state = 0;
}

void Fly::reset()
{
	x = -sprite.getWidth();
	y = sprite.getHeight();
	offset = 0;
	alpha = 0;
	alpha_state = false;
	state = 0;
	direction = 0;
	counter = 0;
	sprite.setPosition( x, sprite.getHeight() );
	
	floor = 0;
	floor_state = 0;
}



void Fly::load( int screen_w, int screen_h, string path )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Set stuff.
	MyFile file;
	file.load( "data/txt/enemy/flying/" +path +".txt" );
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
	
	sprite.setName( "fly-sprite" );
	sprite.load( "data/04_platform/enemy/flying/"+path +".png", line );
	x = -sprite.getWidth();
	y = sprite.getHeight();
	sprite.setPosition( x, y );
	sprite.setScale( scale, scale );
	floor_state = rand() %2;
	
	counter_line = 60;
}

void Fly::draw( sf::RenderWindow* &window )
{
	// printf( "x%d y%d\n", sprite.getX(), sprite.getY() );
	if( state > 0 && sprite.getRight() > 0 && sprite.getX() < screen_w +sprite.getWidth() )
	{
		sprite.setOffset( offset /delay );
		window->draw( sprite.get() );
	}
}



void Fly::fadein( int j, int max )
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

void Fly::fadeout( int j, int min )
{
	alpha_state = false;
	sprite.fadeout( j, min );
	alpha = sprite.getAlpha();
}




void Fly::moveX( sf::Uint8 d, float v )
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

void Fly::undoFall( sf::Uint8 add )
{
	x += add;
	sprite.setPosition( x, sprite.getY() );
}

void Fly::mechanics()
{
	if( state > 0 )
	{
		if( sprite.getX() -sprite.getWidth() > screen_w *2 ||
			sprite.getX() < -screen_w)
		{
			state = 0;
		}
		else
		{
			offset ++;
			if( offset == line *delay )
			{
				offset = 0;
			}
			
			if( direction == 1 )
			{
				x += vel;
			}
			else
			{
				x -= vel;
			}
			
			if( floor_state == 0 )
			{
				floor = rand()% (0xFF /2) +(0xFF/2);
				floor_state = rand()%2 +1;
			}
			else if( floor_state == 1 )
			{
				y += vel /4;
				floor --;
			}
			else
			{
				y -= vel /4;
				floor --;
			}
			
			
			if( floor == 0 )
			{
				floor_state = 0;
			}
			
			sprite.setPosition( x, y );
		}
	}
	else
	{
		counter ++;
		if( counter >= counter_line )
		{
			counter = 0;
			if( rand()%2 == 1 )
			{
				state = 1;
				direction = rand()%2 +1;
				
				if( direction == 1 )
				{
					x = -rand()%screen_w;
					sprite.setScale( scale, scale );
				}
				else
				{
					x = screen_w +rand()%screen_w;
					sprite.setScale( -scale, scale );
				}
				
				y = rand() %(screen_h/2);
				
				sprite.setPosition( x, y );
				floor_state = 0;
			}
		}
	}
}

void Fly::setColor( sf::Color color )
{
	sprite.setColor( color );
}