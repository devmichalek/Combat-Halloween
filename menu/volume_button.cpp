#include "volume_button.h"
#include "own/file.h"

Volume_button::Volume_button()
{
	free();
}

Volume_button::~Volume_button()
{
	free();
}

void Volume_button::free()
{
	plus.free();
	minus.free();
	
	volume = 0;
	min = 0;
	max = 100;
	
	active = true;
	plus_pressed = false;
	minus_pressed = false;
	
	click.free();
}



void Volume_button::load( float left, float right, float bot, float screen_w, float screen_h )
{
	free();
	
	// Load plus button.
	plus.setIdentity( "volume_button-plus" );
	plus.load( "images/menu/plus.png", 3 );
	plus.setScale( screen_w /2560, screen_h /1440 );
	plus.setPosition( right -plus.getWidth(), bot -plus.getHeight() /1.2 );
	
	// Load minus button.
	minus.setIdentity( "volume_button-minus" );
	minus.load( "images/menu/minus.png", 3 );
	minus.setScale( screen_w /2560, screen_h /1440 );
	minus.setPosition( left, bot -minus.getHeight() /1.2 );
	
	// Load chunk.
	click.setIdentity( "volume_button-click" );
	click.load( "sounds/click.wav" );
}

bool Volume_button::handle( sf::Event& event )
{
	if( event.type == sf::Event::MouseButtonReleased )
	{
		if( active )
		{
			plus.setOffset( 0 );
			minus.setOffset( 0 );
			plus_pressed = false;
			minus_pressed = false;
		}
	}
	
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			float x = event.mouseButton.x;
			float y = event.mouseButton.y;
			
			if( plus.checkCollisionCircle( x, y ) )
			{
				if( active )
				{
					if( volume < max )
					{
						click.play();
					}
					
					plus_pressed = true;
				}
				
				return true;
			}
			else if( minus.checkCollisionCircle( x, y ) )
			{
				if( active )
				{
					if( volume > min )
					{
						click.play();
					}
					
					minus_pressed = true;
				}
				
				return true;
			}
		}
	}
	
	return false;
}

void Volume_button::draw( sf::RenderWindow* &window )
{
	window->draw( plus.get() );
	window->draw( minus.get() );
}

void Volume_button::mechanics( double elapsedTime )
{
	if( !active )
	{
		plus.setOffset( 2 );
		minus.setOffset( 2 );
	}
	
	if( plus_pressed && volume < max )
	{
		volume += elapsedTime *0xFF /4;
		if( volume > max )
		{
			volume = max;
		}
		
		plus.setOffset( 1 );
	}
	else if( minus_pressed && volume > min )
	{
		volume -= elapsedTime *0xFF /4;
		if( volume < min )
		{
			volume = min;
		}
		
		minus.setOffset( 1 );
	}
}



void Volume_button::fadein( float v, int max )
{
	plus.fadein( v, max );
	minus.fadein( v, max );
}

void Volume_button::fadeout( float v, int min )
{
	plus.fadeout( v, min );
	minus.fadeout( v, min );
}



void Volume_button::setMainVolume( float volume )
{
	this->volume = volume;
}

float Volume_button::getMainVolume()
{
	return volume;
}

void Volume_button::setActive( bool active )
{
	this->active = active;
	
	if( active )
	{
		plus.setOffset( 0 );
		minus.setOffset( 0 );
	}
}

bool Volume_button::isChanged()
{
	if( plus_pressed || minus_pressed )
	{
		return true;
	}
	
	return false;
}



void Volume_button::setPlayable( bool playable )
{
	click.setPlayable( playable );
}

void Volume_button::setVolume( float volume )
{
	click.setVolume( volume );
}
