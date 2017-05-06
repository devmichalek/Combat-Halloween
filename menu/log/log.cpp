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
	
	play = true;
	click.free();
}



void Log::load( string path, float x, float y )
{
	button.setName( "log-button" );
    button.load( "data/menu/" + path + ".png", 4 );
	button.setScale( 0.5, 0.5 );
	button.setPosition( x, y );
	
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

bool Log::handle( sf::Event &event )
{
	bool pressed = false;
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
						
					if( button.checkCollision( x, y ) && !state )
					{
						explanator.run();
						explanator.focus( x, y );
						button.setOffset( 1 );
					}
				}

				if( event.type == sf::Event::MouseButtonPressed )
				{
					x = event.mouseButton.x;
					y = event.mouseButton.y;
						
					if( button.checkCollision( x, y ) )
					{
						button.setOffset( 2 );
						pressed = true;
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
	
	return pressed;
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
	return button.getRight();
}

const bool& Log::getState()
{
	return state;
}

void Log::setExplanator( string line )
{
	explanator.load( line );
}

float Log::getXCenter()
{
	return button.getX() +button.getWidth() /2;
}

float Log::getBot()
{
	return button.getBot();
}