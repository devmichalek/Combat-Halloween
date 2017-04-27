/**
    log.h
    Purpose: class Log - for simple buttons, after click you have clear window to show own stuff.

    @author Adrian Michalek
    @version 2016.10.07
	@email adrmic98@gmail.com
*/

#include "log.h"


Log::Log( bool locked )
{
    state = false;
	this->locked = locked;
	
	play = true;
}

Log::~Log()
{
	free();
}

void Log::free()
{
	explanator.free();
	state = false;
	locked = false;
	
	button.free();
	y_state = 0;
	left_state = 0;
	left_buf = 0;
	
	play = true;
	click.free();
	scale = 1;
}



void Log::load( string path, unsigned w, unsigned h, float left, float y )
{
	scale = 0.45;
	button.setName( "log-button" );
    button.load( "data/menu/" + path + ".png", 4 );
	
	y_state = h/2 -(y +10);
	left_buf = left;
	left_state = w/2 -left;
	
	button.setPosition( left, y );
	
	// if is locked we don't have reason to load futher
	if( locked )
	{
		button.setOffset( 3 );
	}
	else
	{
		click.setID( "log-click" );
		click.load( "data/menu/click.wav", 50 );
	}
}

void Log::draw( sf::RenderWindow* &window )
{
	if( !state )
	{
		window->draw( button.get() );
		explanator.draw( *window );
	}
}

void Log::handle( sf::Event &event, int r_x, int r_y )
{
	static bool rel = false;
	
	if( !locked )
	{
		if( button.getAlpha() == 0xFF )
		{
			if( !state )
			{
				int x, y;
				explanator.stop();
				button.setOffset( 0 );
				
				if( event.type == sf::Event::MouseMoved )
				{
					x = event.mouseMove.x;
					y = event.mouseMove.y;
						
					if( button.checkCollision( x +r_x, y +r_y ) && !state )
					{
						explanator.run();
						explanator.focus( x +r_x, y +r_y );
						button.setOffset( 1 );
					}
				}

				if( event.type == sf::Event::MouseButtonPressed )
				{
					x = event.mouseButton.x;
					y = event.mouseButton.y;
						
					if( button.checkCollision( x +r_x, y +r_y ) )
					{
						button.setOffset( 2 );
						
						if( play )
						{
							click.play();
						}
						
						state = true;
					}
				}
			}
			else
			{
				
				if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) && !rel )
				{
					if( play )
					{
						click.play();
					}
						
					state = false;
					
					rel = true;
				}
			}
			
			if( event.type == sf::Event::KeyReleased )
			{
				rel = false;
			}
		}
	}
}



void Log::fadein( int i, int max )
{
	button.fadein( i, max );
}

void Log::fadeout( int i, int min )
{
	button.fadeout( i, min );
}



float Log::getRight()
{
	return left_buf +button.getWidth() *scale;
}

const bool& Log::getState()
{
	return state;
}

void Log::setExplanator( string line )
{
	explanator.load( line );
}



void Log::setScale( float s_x, float s_y )
{
	button.setBasicScale( s_x, s_y );
	button.setScale( scale, scale );
	
	explanator.setScale( s_x, s_y );
}

void Log::setView( unsigned w, unsigned h, int r_x, int r_y )
{
	button.setPosition( w/2 -(left_state *button.getXScale() /scale) +r_x, h/2 -(y_state *button.getYScale() /scale) +r_y );
}